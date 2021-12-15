#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define INPUT "./input.txt"
#define SIZE 10

int octopuses[SIZE][SIZE];

// NOTE:
// lines with this comment: '//for part2'
// they are only important to part 2 solution.

void dumpOctopuses() {
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            cout << " " << octopuses[i][j];
        }
        cout << endl;
    }
}

void increaseByOne(){
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            octopuses[row][col] += 1;
        }
    }
}

int flashcount = 0;
void flash(int row, int col){
    flashcount++;
    octopuses[row][col] = -1;   //when flashes its energy is set to -1

    if (row > 0){
        if(col > 0){
            if(octopuses[row-1][col-1] != -1) {
                octopuses[row-1][col-1] += 1;
                if(octopuses[row-1][col-1] > 9 ) flash(row-1,col-1);
            }
        }
        if(octopuses[row-1][col] != -1) {
            octopuses[row-1][col] += 1;
            if(octopuses[row-1][col] > 9 ) flash(row-1,col);
        }
        if(col < SIZE - 1){
            if (octopuses[row-1][col+1] != -1) {
                octopuses[row-1][col+1] += 1;
                if(octopuses[row-1][col+1] > 9 ) flash(row-1,col+1);
            }
        }
    }
    if (row < SIZE){
        if(col > 0){
            if(octopuses[row][col-1] != -1) {
                octopuses[row][col-1] += 1;
                if(octopuses[row][col-1] > 9 ) flash(row,col-1);
            }
            if(row < SIZE - 1){
                if(octopuses[row+1][col-1] != -1){
                    octopuses[row+1][col-1] += 1;
                    if(octopuses[row+1][col-1] > 9 ) flash(row+1,col-1);
                }
            }
        }
        if(row < SIZE - 1){
            if(octopuses[row+1][col] != -1) {
                octopuses[row+1][col] += 1;
                if(octopuses[row+1][col] > 9 ) flash(row+1,col);
            }
        }
        if(col < SIZE - 1){
            if(row < SIZE - 1){
                if(octopuses[row+1][col+1] != -1) {
                    octopuses[row+1][col+1] += 1;
                    if(octopuses[row+1][col+1] > 9 ) flash(row+1,col+1);
                }
            }
            if(octopuses[row][col+1] != -1) {
                octopuses[row][col+1] += 1;
                if(octopuses[row][col+1] > 9 ) flash(row,col+1);
            }
        }
    }
}


int flashed = 0;         //for part2
bool allFlashed = false; //for part2

void setFlashedToZero(){
    flashed = 0;    //for part2
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(octopuses[i][j] < 0) {
                octopuses[i][j] = 0; 
                flashed++;    //for part2
            }
        }
    }

    //for part2
    if(flashed == 100){
        allFlashed = true;
    }
}

int stepcount = 0;
void step(){
    ++stepcount;
    increaseByOne();
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            if(octopuses[row][col] > 9){
                flash(row,col);
            }
        }
    }
    setFlashedToZero();
}

void part1(){
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    int rowcount = 0;
    while(getline(input,line)){
        istringstream iss(line);
        char c;
        string s;
        int colcount = 0;
        while(iss >> c){
            s = c;
            octopuses[rowcount][colcount++] = stoi(s);
        }
        rowcount++;
    }
    input.close();
    
    // dumpOctopuses();

    while(stepcount < 100){
        step();
    }
    cout << "part1: " << flashcount << endl;
}

void part2(){
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    int rowcount = 0;
    while(getline(input,line)){
        istringstream iss(line);
        char c;
        string s;
        int colcount = 0;
        while(iss >> c){
            s = c;
            octopuses[rowcount][colcount++] = stoi(s);
        }
        rowcount++;
    }
    input.close();

    dumpOctopuses();

    stepcount = 0;
    flashcount = 0;
    while(!allFlashed){
        step();
    }
    cout << "part2: " << stepcount << endl;
}

int main(){
    part1();
    part2();
    return 0;
}