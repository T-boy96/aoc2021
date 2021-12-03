#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void part1(){
    ifstream input("./input.txt");
    if(input.fail()) return;

    int h_pos = 0;  //horizontal position
    int depth = 0;
    
    string commd;
    int x;
    while(input >> commd >> x) {
        if(!commd.compare("forward"))    h_pos += x;
        else if (!commd.compare("down")) depth += x;
        else if (!commd.compare("up"))   depth -= x;
    }
    cout << "part1: " << h_pos*depth << endl;
    input.close();
}

void part2(){
    ifstream input("./input.txt");
    if(input.fail()) return;

    int h_pos = 0;  //horizontal position
    int aim = 0;
    int depth = 0;

    string commd;
    int x;

    while(input >> commd >> x){
        if (!commd.compare("down")) aim += x;
        else if (!commd.compare("up")) aim -= x;
        else if (!commd.compare("forward")) {h_pos += x; depth += aim * x;}
    }
    cout << "part2: " << h_pos*depth << endl;

    input.close();
}

int main(){
    part1();
    part2();
    return 0;
}