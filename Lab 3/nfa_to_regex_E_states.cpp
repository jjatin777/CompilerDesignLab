#include<bits/stdc++.h>
using namespace std;
int counter = 0;
set<string> states, input;
string multiply_operator(string& reg){
    string expanded_reg;
    int op = 0;
    for(int i = 0; i < reg.length(); i++){
        if(isspace(reg[i])) continue;
        if(op == 1){
            if(reg[i] == '('){
                expanded_reg.push_back('?');
                op = 0;
            }
            if(reg[i] == '+')
                op = 0;
        }
        if(isdigit(reg[i]) || isalpha(reg[i])){
            if(op == 1){
                expanded_reg.push_back('?');
            }
            op = 1;
        }
        expanded_reg.push_back(reg[i]);
    }
    return expanded_reg;
}

string postfix(string& reg){
    stack <char> st;
    string output;
    unordered_map<char,int> umap;
    umap['*'] = 1;umap['?'] = 2;umap['+'] = 3;
    for(int i = 0; i < reg.size(); i ++){
        if(isdigit(reg[i]) || isalpha(reg[i])){
            output.push_back(reg[i]);
        }else{
            if(reg[i] == '+' || reg[i] == '?'){
                while(!st.empty() && st.top()!='(' && umap[st.top()] <= umap[reg[i]]){
                    output.push_back(st.top());
                    st.pop();
                }
                st.push(reg[i]);
            }else if(reg[i]=='('){
                st.push(reg[i]);
            }else if(reg[i]==')'){
                while(st.top() != '('){
                    output.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }else{
                output.push_back('*');
            }
        }
    }
    while(!st.empty()){
        output.push_back(st.top());
        st.pop();
    }
    return output;
}

struct node{
    int id;
    unordered_map<string,unordered_map<char,vector<string>>> table;
    node(){
        id = counter;
    }
};
void create(node & a, char ch){
    a.table["s"+to_string(a.id)][ch].push_back("e"+to_string(a.id));
   
}
node join(node & f, node& s, char op){
    node result;
    string a,b,c;
    if(op == '+'){
        result.id = counter;
        result.table["s"+to_string(counter)]['E'].push_back("s"+to_string(f.id));
        result.table["s"+to_string(counter)]['E'].push_back("s"+to_string(s.id));

        // s(result )--epsilon--> s(s)
        //     |epsilon
        //     -->s(f.id)
        
        for(auto x: f.table){
            for(auto y: x.second){
                result.table[x.first][y.first] = y.second;
            } 
        }
        for(auto x: s.table){
            for(auto y: x.second){
                result.table[x.first][y.first] = y.second;
            } 
        }

        result.table["e"+to_string(f.id)]['E'].push_back("e"+to_string(counter));
        result.table["e"+to_string(s.id)]['E'].push_back("e"+to_string(counter));
    }else if(op == '?'){
        result.id = counter;

        // s(result)--epsilon-->s(f)- ->e(f)--epsilon-->s(s)-- -->e(s)--epsilon-->e(result)
        result.table["s"+to_string(counter)]['E'].push_back("s"+to_string(f.id));
        for(auto x: f.table){
            for(auto y: x.second){
                result.table[x.first][y.first] = y.second;
            }
        }
        result.table["e"+to_string(f.id)]['E'].push_back("s"+to_string(s.id));
        for(auto x: s.table){
            for(auto y: x.second){
                result.table[x.first][y.first] = y.second;
            }
        }
        result.table["e"+to_string(s.id)]['E'].push_back("e"+to_string(counter));
    }else{
        result.id = counter;
        //     |---e(s)<---   ---s(s)-|
        // s(result)---epsilon--->e(result)

        result.table["s"+to_string(counter)]['E'].push_back("e"+to_string(counter));
        for(auto x: s.table){
            for(auto y: x.second){
                result.table[x.first][y.first] = y.second;
            }
        }
        result.table["e"+to_string(counter)]['E'].push_back("s"+ to_string(s.id));
        result.table["e"+ to_string(s.id)]['E'].push_back("s"+ to_string(counter));
    }
    return result;
}
node nfa(string regex){
    stack<node> st;
    for(int i = 0; i < regex.size(); i ++){
        counter++;
        if(isdigit(regex[i]) || isalpha(regex[i])) {
            node a;
            create(a,regex[i]);
            st.push(a);
        }else if(regex[i] == '+' || regex[i] == '?'){
            node c = st.top(); st.pop();
            node b = st.top(); st.pop();
            st.push(join(b,c,regex[i]));
        }else{//*
            node b = st.top(); st.pop();
            st.push(join(b,b,regex[i]));
        }
    }
    return st.top();
}
// abc+?x*?f?*
int main(){
    string regex = "(a(b+c)e*f)*";
    cin >> regex;
    regex = multiply_operator(regex);
    regex = postfix(regex);
    
    cout << regex<<endl;
    node result =nfa(regex); 
    cout << "s"+ to_string(result.id) <<" "<<"e"+ to_string(result.id)<<endl;
    cout << "state "<<" input "<<" output state\n";
    for(auto x: result.table){
        for(auto y: x.second){
            cout << x.first << " " << y.first << " ";
            for(auto z: y.second){
                cout<< z <<" ";
            }
            cout << endl;
        }
    }
}

//  1a2 3(b+c)4 5e*6 7f8

                    
//   a                    b  c
// s e1                e1 e2 e2

//    E 
// e2 b 
//   E
// b e3
//    x 
// e3 e2

//    f
// e3 e
  
// e = s1


// s->b->e

//    E 
// s1 b 
//   E
// b e
    
// e= s

//    x
// s1 e
//    E
// e  s2


// x*
//    E
// s2 b
//   E
// b e
//   E
// e s1

 s5 e5
state  input  output state
e4 E e5
s4 c e4
e3 E s4
s5 E s3
s3 E s1 s2
s1 a e1
e1 E e3
e2 E e3
s2 b e2