#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &n, vector<int> &s, vector<char> &g){
    ifstream F(filename);
    string T;
    while(getline(F,T)){
        const char *text = T.c_str();
        char format[] = "%[^:]: %d %d %d";
        char Name[100];
        int x,y,z,sum;
        sscanf(text,format,Name,&x,&y,&z);
        string N = Name;
        n.push_back(N);
        sum = x+y+z;
        s.push_back(sum);
        g.push_back(score2grade(sum));
    }

}

void getCommand(string &command, string &key){
    cout << "Please input your command:" << endl;
    string input;
    getline(cin,input);
    int A = input.find(" ");
    command = input.substr(0,A);
    key = input.substr(A+1);
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    
    for(unsigned i = 0; i < names.size() ; i++){
        if(key == toUpperStr(names[i])){
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
            break;
        }
        
        if(i == names.size()-1){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
        }
    }
    
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool z;
    cout << "---------------------------------" << endl;
    for(unsigned i = 0 ; i < grades.size() ; i++){
        if(key[0] == grades[i]){
            z = true;
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
        
        if(i == grades.size()-1 && !z){
        cout << "Cannot found." << endl;
        }
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}