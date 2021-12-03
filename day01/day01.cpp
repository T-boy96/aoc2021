#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void part1(){
    ifstream input("./input.txt");
    if(input.fail()) return;
    int depthbefore = -1;
    int res = 0;
    int d;
    while (input >> d) {
        if (depthbefore != -1 && d > depthbefore){
            res++;
        }
        depthbefore = d;
    }
    cout << "part1: " << res << endl;
    input.close();
}

void part2(){
    ifstream input("./input.txt");
    if(input.fail()) return;
    int a,b,c,d;
    vector<int> t;
    a = -1;
    int res = 0;
    while(input >> d) {
        if(t.size() < 3) t.push_back(d);
        else{
            if(t.size() == 3 && (t[1] + t[2] + d) > (t[0] + t[1] + t[2])){
                res++;
            }
            
            t[0] = t[1];
            t[1] = t[2];
            t[2] = d;
        }
    }
    cout << "part2: " << res << endl;
    input.close();
}

int main(){
    part1();
    part2();
    return 0;
}