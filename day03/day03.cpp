#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input.txt");
    if (input.fail()) return;
    
    string line;
    vector<vector<char>> container;

    while(getline(input,line)){
        vector<char> value;
        for(int i = 0; i < line.size(); i++){
            value.push_back(line[i]);
        }
        container.push_back(value);
    }
    
    string gamma = "";
    string epsilon = "";
    for(int j = 0; j < container[0].size(); j++){
        int count = 0;
        for(int i = 0; i < container.size(); i++){
            if(container[i][j] == '1') count++;
            else count--;
        }
        
        if(count > 0) {gamma += '1'; epsilon += '0';}
        else {gamma += '0'; epsilon += '1';}
    }

    cout << "part1: " << stoi(gamma,0,2) * stoi(epsilon,0,2) << endl;
    input.close();
}

// PART 2
vector<string> filter_oxygen( vector<string> c, int pos) {
    int count = 0;
    
    for(int i = 0; i < c.size(); i++){
        if( c[i][pos] == '1') count++;
        else count--;
    }
        
    vector<string> res;

    if(count >= 0) {
        for(int i = 0; i < c.size(); i++){
            if( c[i][pos] == '1') {
                res.push_back(c[i]);
            }
        }
    }else {
        for(int i = 0; i < c.size(); i++){
            if( c[i][pos] == '0') {
                res.push_back(c[i]);
            }
        }
    }
    return res;
}

vector<string> filter_co2( vector<string> c, int pos) {
    int count = 0;
    vector<string> res;
    
    
    for(int i = 0; i < c.size(); i++){
        if( c[i][pos] == '1') count++;
        else count--;
    }
        
    if(count >= 0) {
        for(int i = 0; i < c.size(); i++){
            if( c[i][pos] == '0') {
                res.push_back(c[i]);
            }
        }
    }else{
        for(int i = 0; i < c.size(); i++){
            if( c[i][pos] == '1') {
                res.push_back(c[i]);
            }
        }
    }
    return res;
}

void part2(){
    ifstream input("./input.txt");
    if(input.fail()) return;

    string line;
    vector<string> container;

    while(getline(input,line)){
        string value = "";
        for(int i = 0; i < line.size(); i++){
            value += line[i];
        }
        container.push_back(value);
    }

    vector<string> filtered_ox = container;
    vector<string> filtered_co2 = container;
    
    int pos = 0;
    while( filtered_ox.size() > 1 ){
        filtered_ox = filter_oxygen(filtered_ox, pos);
        pos++;
    }
    pos = 0;
    while( filtered_co2.size() > 1 ){
        filtered_co2 = filter_co2(filtered_co2, pos);
        pos++;
    }
    cout << "part2: " << stoi(filtered_ox[0],0,2) * stoi(filtered_co2[0],0,2) << endl;

    input.close();
}

int main(){
    part1();
    part2();
    return 0;
}