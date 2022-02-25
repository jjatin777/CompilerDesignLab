#include<bits/stdc++.h>
using namespace std;
vector<string> reserved = {"asm","auto","bool","break","case","catch","char","class","const","const_cast","continue","default","delete","do","double","dynamic_cast","else","enum","explicit","export","extern","false","float","for","friend","goto","if","inline","int","long","mutable","namespace","new","operator","private","protected","public","register","reinterpret_cast","return","short","signed","sizeof","static","static_cast","struct","switch","template","this","throw","true","try","typedef","typeid","typename","union","unsigned","using","virtual","void","volatile","wchar_t","while"};
vector<string> libraries = {"bits/stdc++.h","cin","cout","iostream","string","unordered_map","vector"};
vector<string> type = {"NONE","Operator","Keywords","Identifiers","Literals","Punctuators"};
 
void func(unordered_map <string, int>& umap,string &code);
int main(){
    string text,code;
    unordered_map <string,int> umap;
    ifstream file("tt.cpp");

    while (getline (file, text)) {
        code += text; 
    }
    func(umap, code);

    for(int i = 1; i < type.size(); i++){
        for(auto y: umap){
            if( y.second == i){
                cout << type[i] << " " << y.first << endl;
            }
        }
    }
    file.close();
}

void func(unordered_map <string,int>& umap,string &code){
    string st;
    for(int i = 0; i < code.size(); i++){
      
        while(isspace(code[i]) || code[i] == '\n' || code[i] == ';') i++;
        st = "";
        if(code[i] == ',' || code[i] == '(' || code[i] == ')' || code[i] == '{' || code[i] == '}' || code[i] == '#' || code[i] == ';'){
            
            st = code[i];
            umap[st] = 5;//puntuators
        }else if( code[i] == '+' || code[i] == '=' || code[i] == '-' || code[i] == '*' || code[i] == '^' || code[i] == '%' || code[i] == '!' ||code[i] == '/' || code [i] == '<' || code[i] == '>' || code [i] == '&'){
        
            st = "";
            st = code[i];
            i++;
            if( code[i-1] == '<' || code[i-1] == '>'){
                if( code[i] == '<' || code[i] == '>' ){
                    st.push_back(code[i]);
                    umap[st] = 1; //operator;
                }else {
                    i--;
                    umap[st] = 5; //; 
                }
            }
            else if( code[i] == '+' || code[i] == '=' || code[i] == '-' || code[i] == '*' || code[i] == '^' || code[i] == '%' || code[i] == '!' ||code[i] == '/'){
                st.push_back(code[i]);
                umap[st] = 1; //operator;
            }else{
                i--;
                umap[st] = 1; //operator;
            }   
        }else if((i>=2 && code[i-1] == '=' && code[i-2] != '=') || (i>=3 && code[i-2] == '=' && code[i-3] != '=') ){
            st = code[i];
            i++;
            while(code[i] != ',' && code[i] != ';'){
                if(isspace(code[i])) continue;
                st.push_back(code[i]);
                i++;
            }
            umap[st] = 4; //literals
        }else if( code[i] == '\"' ){
            st = code[i];
            i++;
            while( code[i] != '\"'){
                st.push_back(code[i]);
                i++;
            }
            st.push_back(code[i]);
            umap[st] =  4; //literals
        }else if( code[i] == '\'' ){
            st = code[i];
            i++;
            while( code[i] != '\''){
                st.push_back(code[i]);
                i++;
            }
            st.push_back(code[i]);
            umap[st] =  4; //literals
        }else{
            while(i< code.size() && ( !isspace(code[i]) && code[i] != ';' && code[i] != '=' && code[i] != '(' && code[i] != '<' && code[i] != '>' && code[i] != ')' && code[i] != '+' && code[i] != '-' && code[i] != '/' && code[i] != '*' && code[i] != ',' && code[i] != '}')){
                st.push_back(code[i]);
                i++;
            }
            i--;
            if(i+1 < code.size() && code[i+1]=='('){
                umap[st] = 3; //Identifiers
            }else if (binary_search(reserved.begin(),reserved.end(),st) ){
                umap[st] = 2; //keyword;
            }else if (binary_search(libraries.begin(),libraries.end(),st) ){
                umap[st] = 3; //Identifiers
            }else{
                umap[st] = 3; //Identifiers
            }
        }
    }
}

