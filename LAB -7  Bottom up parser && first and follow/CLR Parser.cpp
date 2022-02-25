#include<bits/stdc++.h>
using namespace std;

// E->T | T + E
// T-> int | int * T|(E)
// Epsilon 0 || E 1 || T 2 || int 3 || * 4 || + 5 || ( 6 || ) 7 || $ 8
vector<string> val = {"Ep","E","T","int","*","+","(",")","$","","s","r"};

void pre(unordered_map<int,unordered_map<int,pair<char,int>>>& ActionTable, 
unordered_map<int,unordered_map<int,int>>& GotoTable,
unordered_map<string,int>& states,
vector<vector<int>>& rules
){
    states["E"] = 1; states["T"] = 2; 
    states["int"] = 3; states["*"] = 4;states["+"] = 5;
    states["("] = 6;states[")"] = 7;states["$"]= 8;
    states[""]=0; states["s"]= 9; states["r"] = 10;

    rules.push_back({0,1});       //E'->E
    rules.push_back({1,1});       //E->T 
    rules.push_back({1,3});   //E->T + E
    rules.push_back({2,1});       //T-> int
    rules.push_back({2,3});   //T->int * T
    rules.push_back({2,3});   //T->(E)

    ActionTable[0][6]=make_pair('s',3); ActionTable[0][3] = make_pair('s',4); GotoTable[0][2] = 2; GotoTable[0][1] = 1;
    ActionTable[1][8] = make_pair('A',100);
    ActionTable[2][5] = make_pair('s',5); ActionTable[2][8] = make_pair('r',1); 
    ActionTable[3][6] = make_pair('s',12);ActionTable[3][3] = make_pair('s',9);GotoTable[3][2] = 8;GotoTable[3][1] = 6;
    ActionTable[4][5] = make_pair('r',3);ActionTable[4][4] = make_pair('s',17); ActionTable[4][8] = make_pair('r',3);
    ActionTable[5][6] = make_pair('s',3);ActionTable[5][3] = make_pair('s',4); GotoTable[5][2] = 2;GotoTable[5][1] = 6;
    ActionTable[6][7] = make_pair('s',7);ActionTable[6][8] = make_pair('r',2);
    ActionTable[7][5] = make_pair('r',5);ActionTable[7][8] = make_pair('r',5);
    ActionTable[8][5] = make_pair('s',13);ActionTable[8][7] = make_pair('r',1);
    ActionTable[9][5] = make_pair('r',3);ActionTable[9][4] = make_pair('s',10);ActionTable[9][7] = make_pair('r',3);
    ActionTable[10][6] = make_pair('s',12);GotoTable[10][2] = 11;
    ActionTable[11][4] = make_pair('r',4);ActionTable[11][7] = make_pair('r',4);
    ActionTable[12][6] = make_pair('s',12);ActionTable[12][3] = make_pair('s',9);GotoTable[12][2] = 8;GotoTable[12][1] = 15;
    ActionTable[13][6] = make_pair('s',12);ActionTable[13][3] = make_pair('s',9);GotoTable[13][2] = 8;GotoTable[13][1] = 14;
    ActionTable[14][7] = make_pair('r',2);
    ActionTable[15][7] = make_pair('s',16);
    ActionTable[16][7] = make_pair('r',5);
    ActionTable[17][6] = make_pair('s',3);ActionTable[17][3] = make_pair('s',4);GotoTable[17][2] = 18;
    ActionTable[18][5] = make_pair('r',4);ActionTable[18][8] = make_pair('r',4);
}

int main(){
    unordered_map<int,unordered_map<int,pair<char,int>>> ActionTable;
    unordered_map<int,unordered_map<int,int>> GotoTable;
    unordered_map<string,int> states;
    vector<vector<int>> rules;

    pre(ActionTable,GotoTable,states,rules);

    vector <pair<int,int>> st;

    int i =0,error = 0;

    // Tokennizing the input (space separated input expected)
    string input,s="";
    vector<int> arr;
    getline(cin,input);

    for(int i = 0; i< input.size();i++){
        if(input[i] == ' '){
            arr.push_back(states[s]);
            s= ""; 
        }else{
            s.push_back(input[i]);
        }
    }
    arr.push_back(states[s]); 
    arr.push_back(states["$"]); 
  
    // parsing
    int sig = 0;
    st.push_back( make_pair(states["$"],0) );

    while(!st.empty() && i < arr.size()){
        pair<int,int> t = st.back();
        for(auto rex: st) cout << val[rex.first]<<" "<<rex.second<<" ";
            cout << endl;

        if(ActionTable[t.second][arr[i]].second == 0){
            break;
        }
        if(ActionTable[t.second][arr[i]].first == 'A'){
            cout << "Accepted" <<endl;
            sig = 1;
            break;
        }
        // cout << ActionTable[t.second][arr[i]].first<<" "<<ActionTable[t.second][arr[i]].second<<endl;
        if(ActionTable[t.second][arr[i]].first == 's'){

            st.push_back(make_pair(arr[i],ActionTable[t.second][arr[i]].second));
            i++;

        }else if(ActionTable[t.second][arr[i]].first == 'r'){

            int stz =  rules[ ActionTable[t.second][arr[i]].second ][0]; // State that will reduce to
            int len = rules[ ActionTable[t.second][arr[i]].second ][1]; // number of elements to be erased
            while(len--){
                st.pop_back();
            }
            // cout << "Here\n";
            // for(auto rex: st) cout << rex.first<<" "<<rex.second<<" ";
            // cout << endl;
            
            int xx = GotoTable[st.back().second][stz];
            st.push_back(make_pair(stz ,xx));
        }
        
    }
    if(sig == 0)   
        cout <<"NO Match Found"<<endl;
}