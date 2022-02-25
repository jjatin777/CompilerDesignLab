#include<bits/stdc++.h>
using namespace std;

int nextt = 0;
vector<string> arr;

bool E(int level);
bool T(int level);

bool match(string s){
    cout <<"M ";
    // cout <<"match "<< nextt <<" "<<arr[nextt]<<" "<<s<<endl;
    if(nextt >= arr.size()) return false;
    return (arr[nextt++] == s);
}
bool T1(int level){
    cout <<"T1 ";
    int save = nextt;
    return match("int");
}
bool T2(int level){
    level++;
    cout <<"T2 ";
    int save = nextt;
    return (match("int") && match("*") && T(level));
}

bool T3(int level){
    level++;
    cout <<"T3 ";
    return (match("(") && E(level) && match(")"));
}

bool T(int level){
    level++;
    cout <<"T ";

    int save = nextt;
    bool a = T3(level);
    if(a) return a;

    nextt = save;
    bool b = T2(level);
    if(b) return b;

    nextt = save;
    bool c = T1(level);
    if(c) return c;

    return 0;
}

bool E(int level){
    cout << "E ";
    level++;

    int save = nextt;
    bool b = (T(level) && match("+") && E(level));

    if(level == 1){
        if(nextt < arr.size() && arr[nextt] == "$" && b) return b; 
    }else {
        if(b) return b;
    }

    nextt = save;
    bool a = T(level);

    if(level == 1){
        if(arr[nextt] != "$") return 0; 
        else return a;
    }else {
        return a;
    }
    
}

int main(){
    string input,s;
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
    if(E(0)) cout <<"\nString matched";
    else cout <<"\nNOT matched";
}


// E->T | T + E
// T-> int | int * T|(E)
// int * int
// int * ( int )
//  int + int + int + ( int )

// T + E
// (E)
// (T + E)
// (int + int + E)

// T + E
// (E) + E
// (int)

// (int) + int + int * int

