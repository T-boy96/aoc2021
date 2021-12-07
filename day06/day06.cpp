#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <cstring>

#define INPUT "./input.txt"
#define DAYS 256

using namespace std;

class Fish{
private:
    int time;
    int prev = -1;
public:
    Fish() : time(8) {};
    Fish(int t) : time(t) {};
    
    void decr(){
        prev = time--;
    }
    int get(){
        return time;
    }

    int pr(){
        return prev;
    }

    void set(int t){time = t;}
};

void part1(){
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    getline(input,line);
    istringstream iss(line);
    char c;
    vector<Fish> fish;
    while(iss >> c) {
        string s = "";
        s += c;
        if(c != ',') {Fish f = Fish(stoi(s)); fish.push_back(f);}
    }
    input.close();

    int count = 0;
    while(count <= 80){
        // DISPLAY:
        // if(count == 0)                          cout << "Initial state:      ";
        // else if (count == 1)                    cout << "After    " << count << "  day:    ";
        // else if (count < 10)                    cout << "After    " << count << " days:    ";
        // else if (10 <= count && count <= 99)    cout << "After   " <<  count << " days:    ";
        // else if (100 <= count && count <= 999)  cout << "After  " <<   count << " days:    ";
        
        for(int i = 0; i < fish.size(); i++){
            int t = fish[i].get();
            // cout << t << " ";
            
            if(t > 0) {
                if(t == 6 && fish[i].pr() != 7) { 
                    fish.push_back(Fish(8));
                }
                fish[i].decr();
            }
            if(t == 0) { fish[i].set(6);}
        }
        // cout << endl;
        count++;
    }
    cout << "part1: after " << count-1 << " day" << ((count -1 != 1) ? "s " : " ") << "there are " << fish.size() << " lanternfish" << endl;
}

void part2(){
    ifstream input(INPUT);
    string line;
    getline(input,line);
    
    istringstream iss(line);
    char c;
    long long int daysarray[9];
    memset(daysarray,0,sizeof(long long int)*9);

    while(iss >> c){
        string s = "";
        if (c != ',') {
            s += c; 
            for(int j = 1; j <= 8; j++){
                if(stoi(s) == j){
                    daysarray[j] = daysarray[j] + 1;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < DAYS; i++){
        long long int tmp = daysarray[0];
        daysarray[0] = daysarray[1];
        daysarray[1] = daysarray[2];
        daysarray[2] = daysarray[3];
        daysarray[3] = daysarray[4];
        daysarray[4] = daysarray[5];
        daysarray[5] = daysarray[6];
        daysarray[6] = tmp + daysarray[7];
        daysarray[7] = daysarray[8];
        daysarray[8] = tmp;
    }

    long long int sum = 0;
    for(long long int day : daysarray){
            sum +=  day;
    }
    cout << "part2: after " << DAYS << " days there are " << sum << " lanternfish" << endl;
}

int main(){
    part1();
    part2();
    
    return 0;
}