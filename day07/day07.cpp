#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define INPUT "./input.txt"

struct f {
    long long int fuel;
    int position;
};

void part1(){
    ifstream input(INPUT);
    if(input.fail())return;

    string line;
    getline(input, line);
    char c;
    string s = "";
    istringstream iss(line);
    vector<int> crabs;
    while(iss >> c){
        if(c != ',') {
            s += c;
        }
        else {
            if(s != "") { crabs.push_back(stoi(s)); s = "";}
        }
    }
    crabs.push_back(stoi(s));
    input.close();

    long long int avg = 0;
    long long int sum = 0;
    for(int c : crabs) sum += c;
    avg = sum / crabs.size();

    vector<f> fuels;
    for(int i = 0; i <= avg; i++){
        int pos = i;
        long long int sumfuel = 0;
        for(int c : crabs){
            long long int fuel = 0;
            if(c > i){
                while(c > i) {c--; fuel++;}
            }
            else{
                while(c < i) {c++; fuel++;}
            }
            sumfuel += fuel;
        }

        f res;
        res.fuel = sumfuel;
        res.position = pos;
        fuels.push_back(res);
        // cout << "sum at position " << res.position << ": " << res.fuel << " fuel" << endl;
    }
    
    f min = fuels[0];
    for(f fuel : fuels){
        if (fuel.fuel < min.fuel) {
            min.fuel = fuel.fuel;
            min.position = fuel.position;
        }
    }
    cout << "part1: minimal fuel = "<< min.fuel << " at position "<< min.position << endl;

}

void part2() {
    ifstream input(INPUT);
    string line;
    getline(input, line);
    char c;
    string s = "";
    istringstream iss(line);
    
    vector<int> crabs;
    while(iss >> c){
        if(c != ',') {
            s += c;
        }
        else {
            if(s != "") { crabs.push_back(stoi(s)); s = "";}
        }
    }
    crabs.push_back(stoi(s));

    int max = 0;
    for(int c : crabs) if (c > max) max = c;
    vector<f> fuels;
    for(int i = 0; i <= max; i++){
        int pos = i;
        long long int sumfuel = 0;
        for(int c : crabs){
            long long int fuel = 0;
            int count = 0;
            if(c > i){
                while(c > i) {
                    count++;
                    c--; 
                    fuel += count;
                }
            }
            else{
                while(c < i) {
                    count++;
                    c++;
                    fuel += count;
                }
            }
            sumfuel += fuel;
        }

        f res;
        res.fuel = sumfuel;
        res.position = pos;
        fuels.push_back(res);
        // cout << "sum at position " << res.position << ": " << res.fuel << " fuel" << endl;
    }
    
    f min = fuels[0];
    for(f fuel : fuels){
        if (fuel.fuel < min.fuel) {
            min.fuel = fuel.fuel;
            min.position = fuel.position;
        }
    }
    cout << "part2: minimal fuel = "<< min.fuel << " at position "<< min.position << endl;
}

int main(){
    part1();
    part2();
    return 0;
}