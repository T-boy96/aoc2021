#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define INPUT "./input.txt"

class Stack{
private:
    vector<char> stack;
public:
    char pop(){
        stack.pop_back();
    }
    void push(char c){
        stack.push_back(c);
    }
    char top(){
        return stack[stack.size()-1];
    }
    bool isEmpty(){
        return stack.size() == 0;
    }
    void setEmpty(){
        stack.clear();
    }
};

void part1() {
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    vector<char> firstIllegalCharacters;
    while(getline(input, line)){
        istringstream iss(line);
        char c;
        Stack s;
        while(iss >> c){
            if(c == '(' || c == '[' || c == '{' || c == '<'){
                s.push(c);
            }
            else{
                if(s.isEmpty()) break;
                else if(c == ')'){
                    if(s.top() == '(') s.pop();
                    else {firstIllegalCharacters.push_back(c); break;}
                }
                else if(c == ']'){
                    if(s.top() == '[') s.pop();
                    else {firstIllegalCharacters.push_back(c); break;}
                }
                else if(c == '}'){
                    if(s.top() == '{') s.pop();
                    else {firstIllegalCharacters.push_back(c); break;}
                }
                else if(c == '>'){
                    if(s.top() == '<') s.pop();
                    else {firstIllegalCharacters.push_back(c); break;}
                }
            }
        }
        s.setEmpty();
    }
    int result = 0;
    for(char c : firstIllegalCharacters) {
        if(c == ')') result += 3;
        else if(c == ']') result += 57;
        else if(c == '}') result += 1197;
        else if(c == '>') result += 25137;
    }
    cout << "part1: " << result << endl;
}

void part2() {
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    vector<char> completionString;
    vector<long long int> results;
    while(getline(input, line)){
        istringstream iss(line);
        char c;
        Stack s;
        bool corrupted = false;
        while(iss >> c){
            if(c == '(' || c == '[' || c == '{' || c == '<'){
                s.push(c);
            }
            else{
                if(s.isEmpty()) break;
                else if(c == ')'){
                    if(s.top() == '(') s.pop();
                    else {corrupted = true; break;}
                }
                else if(c == ']'){
                    if(s.top() == '[') s.pop();
                    else {corrupted = true; break;}
                }
                else if(c == '}'){
                    if(s.top() == '{') s.pop();
                    else {corrupted = true; break;}
                }
                else if(c == '>'){
                    if(s.top() == '<') s.pop();
                    else {corrupted = true; break;}
                }
            }
        }
        if (!s.isEmpty() && !corrupted){
            while(!s.isEmpty()){
                if(s.top() == '('){
                    completionString.push_back(')');
                    s.pop();
                }
                else if(s.top() == '['){
                    completionString.push_back(']');
                    s.pop();
                }
                else if(s.top() == '{'){
                    completionString.push_back('}');
                    s.pop();
                }
                else if(s.top() == '<'){
                    completionString.push_back('>');
                    s.pop();
                }
            }
        }
        if(completionString.size() > 0){
            long long int result = 0;
            for(char c : completionString){
                result *= 5;
                if(c == ')') result += 1;
                if(c == ']') result += 2;
                if(c == '}') result += 3;
                if(c == '>') result += 4;
            }
            results.push_back(result);
            completionString.clear();
        }
    }

    sort(results.begin(),results.end());
    
    // for(long long int r : results) cout << r << endl;
    
    cout << "part2: " << results[results.size()/2] << endl;
    results.clear();
}

int main(){
    part1();
    part2();
    return 0;
}