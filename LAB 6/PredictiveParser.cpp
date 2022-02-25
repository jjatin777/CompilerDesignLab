#include<bits/stdc++.h>
using namespace std;

// epsilon 0 || E 1 || E' 2 || T 3 || T' 4 || F 5 || + 6 || * 7 || id 8 | ) 9 || ( 10

void pre(unordered_map<string,unordered_map<string,int>>& table, vector<vector<int>>& rules,vector<string>& states){

    states = {"epsilon","E","E'","T","T'","F","+","*","id",")","("};

    rules.push_back({2,3});   //E -> TE`     0
    rules.push_back({2,3,6}); //E'-> +TE`    1
    rules.push_back({});      //E'-> epsilon 2
    rules.push_back({4,5});   //T-> FT`      3
    rules.push_back({});      //T`-> epsilon 4
    rules.push_back({4,5,7}); //T`-> *FT`    5
    rules.push_back({8});     //F -> id      6
    rules.push_back({9,1,10});//F -> (E)     7

    table["E"]["id"] = 0; table["E"]["("] = 0;
    table["E'"]["+"] = 1;table["E'"][")"] = 2;table["E'"]["$"] = 2;
    table["T"]["id"] = 3;table["T"]["("] = 3;
    table["T'"]["+"] = 4;table["T'"]["*"] = 5;table["T'"][")"] = 4;table["T'"]["$"] = 4;
    table["F"]["id"] = 6;table["F"]["("] = 7;

}
int main(){
    unordered_map<string,unordered_map<string,int>> table;
    vector<string> states;
    vector<vector<int>> rules;

    pre(table,rules,states);

    stack <string> st;
    st.push("$");
    st.push("E"); 
    int i =0,error = 0;

    // Tokennizing the input (space separated input expected)
    string input,s;
    vector<string> arr;
    getline(cin,input);

    for(int i = 0; i< input.size();i++){
        if(input[i] == ' '){
            arr.push_back(s);
            s= ""; 
        }else{
            s.push_back(input[i]);
        }
    }
    arr.push_back(s); 
    arr.push_back("$"); 
  
    // parsing
    s = "";
    while(!st.empty() && i < arr.size()){
        input = st.top();
        st.pop();
        for(auto x: rules[table[input][arr[i]]]){
            // cout << states[x];
            st.push(states[x]);
        }
        // cout << endl;
        if(s == st.top()){
            error = 1;
            break;
        }
        

        while(!st.empty() && st.top() == arr[i]){
            i++;
            st.pop();
        }
        if(!st.empty())
            s = st.top();
    }
    // cout << st.empty() << i <<endl;
    if(st.empty() && i == arr.size())
        cout <<"Its a Match"<<endl;
    else    
        cout <<"NO Match Found"<<endl;
}

// E -> T E’
// E’-> + TE’ | є
// T -> F T’
// T’-> * F T’ | є
// F -> (E) | id