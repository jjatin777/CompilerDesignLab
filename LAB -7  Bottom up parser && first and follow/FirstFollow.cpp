#include<bits/stdc++.h>
using namespace std;

int main(){

    int nProds;
    unordered_map<char,int> symbol;
    map< char,vector<string> > prod;
    vector<char> order;
    unordered_map<char,set<char>> FRT,FLW;
    unordered_map<char, set<char> > later;
    int count = 1;
    string lhs,rhs;

    cout << "Enter number of productions\n";
    cin >> nProds;
    cout << "Enter productions, Use # for epsilon and use only single charcter for symbols\n";
    for(int i = 0; i < nProds; i++){
        cin >> lhs >>rhs;
        if( symbol.find(lhs[0]) == symbol.end() )
            order.push_back(lhs[0]);
            symbol[lhs[0]] = i;
        prod[lhs[0]].push_back(rhs);
    }
    cout << endl;
    
    for(int i = order.size()-1; i >= 0; i--){
        symbol[order[i]] = 0;
        for(auto x: prod[order[i]]){
            if( x[0] == '#'){
                FRT[order[i]].insert('#');
            }else{
                if(!isupper(x[0]) ){
                    FRT[order[i]].insert(x[0]);
                }
                else{
                    int j =0;
                    int eps =1;
                    // T FB
                    while(j < x.size() && isupper(x[j]) && eps){
                        eps = 0;
                        for(auto y : FRT[x[j]]){
                            if(y == '#'){
                                eps = 1;
                            }
                            FRT[order[i]].insert(y);
                        }
                        j++;
                        
                        if(j == x.size() || !isupper(x[j]) || eps == 0){
                            FRT[order[i]].erase('#');
                            for(auto y : FRT[x[j-1]]){
                                if(y == '#'){
                                    FRT[order[i]].insert(y);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "First of Non terminals\n";
    for(auto a: FRT){
        cout << a.first << " ";
        for(auto y: a.second){
            cout << y<<" ";
        }
        cout << endl;
    }
    cout << endl;

    FLW[order[0]].insert('$');
    int eps = 0;
    
    for(auto x: prod){
        for(auto y: x.second){
            if(y[0] == '#') continue;
            // y  each rhs of productions of x.first
            if( isupper(y[y.size()-1]) && y[y.size()-1] != x.first) { // adding follow of lhs as follow of rhs[last] if it is non terminal
                later[y[y.size()-1]].insert(x.first);
                symbol[y[y.size()-1]] = 1;
            }

            for(int i =0; i < y.size()-1; i++){ //n2 to calculate whole prod

                if(! isupper(y[i])) continue; // not for terminal

                eps = 1;
                int j = i+1;
                for(j; j <y.size() && eps == 1; j++){
                    eps = 0;
                    if(!isupper(y[j])){ // found terminal,terminate
                        FLW[y[i]].insert(y[j]);
                        break;
                    }
                    for(auto rex: FRT[y[j]]){
                        // cout << y[i] <<" "<<rex << " first of  "<< y[j]<<endl;
                        if(rex == '#'){ 
                            eps = 1; 
                            continue; 
                        }
                        FLW[y[i]].insert(rex);
                    }
                }
                if(eps == 1 && j == y.size() && y[i] != x.first){
                    later[y[i]].insert(x.first);
                    symbol[y[i]] = 1;
                }
            }
        }
    }

    queue<char> q;
    for(auto x: symbol){
        if(x.second == 0) q.push(x.first);
    }

    int sig = 0,sig2 = 0;
    while(!q.empty()){
        
        char ch = q.front();
        // cout << "q.front "<< ch<<endl;
        q.pop();
        for(auto y: later){
            sig = 0;
            sig2 = 0;
            // cout << y.first <<endl;
            for(auto x: y.second){
                sig2 = 1; 
                // cout << x<<" ";
                if(ch == x){
                    for(auto z: FLW[ch]){
                        // cout << y.first <<" "<<z<<endl;
                        FLW[y.first].insert(z);
                    }
                    // cout << y.first <<
                    later[y.first].erase(ch);
                }else{
                    sig = 1;
                }
            }
            if(sig == 0 && sig2 == 1) {
                q.push(y.first);
            }
        }
    }

    cout << "Follow of Non terminals\n";
    for(auto a: FLW){
        cout << a.first << " ";
        for(auto y: a.second){
            cout << y<<" ";
        }
        cout << endl;
    }
}


// 8
// E TA 
// A +TA
// A #
// T FB 
// B *FB
// B #
// F (E)
// F i

// 10
// S ABCDE
// A a
// A #
// B b
// B #
// C c
// D d
// D #
// E e
// E #