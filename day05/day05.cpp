#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

// NOTE:
// - It creates a map.csv file
// - SIZE value is 10 for sample input (which is "./input1.txt")
// - INPUT: path to desired input

#define SIZE 1000
#define INPUT "./input.txt"

class Ventline{
private:
    class Point {
    private:
        int x;
        int y;
    public:
        Point(){
            x = 0;
            y = 0;
        }
        Point(int _x, int _y) {
            x = _x;
            y = _y;
        }
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
        string toString(){
            return "(" + to_string(x) + ", " + to_string(y) + ")";
        }
    };
    Point from;
    Point to;
public:
    Ventline(int x1,int y1,int x2,int y2){
        from = Point(x1,y1);
        to = Point(x2,y2);
    }
    Point start(){
        return from;
    }
    Point end(){
        return to;
    }

    string toString(){
        return "from: " + from.toString() + ", to: " + to.toString() + "\n";
    }
};

int fromline(int* x1, int* y1, int* x2, int* y2, string line){
    int count = 0;
    string n;
    for(int i = 0; i < line.length(); i++){
        char c = line[i];
        if(isdigit(c)){
            n += c;
        }
        else{
            if(n != ""){
                count++;
                if(count == 1) *x1 = stoi(n);
                else if(count == 2) *y1 = stoi(n);
                else if(count == 3) *x2 = stoi(n);
            }
            if(count != 4) n = "";
        }
    }
    *y2 = stoi(n);
}

int map[SIZE][SIZE];

void verticalVentLine(int m[SIZE][SIZE], int x1, int y1, int y2){
    if (y1 > y2) swap(y1,y2);
    for(int j = y1; j <= y2; j++){
        m[x1][j] += 1;
    }
}

void horizontalVentLine(int m[SIZE][SIZE], int y1, int x1, int x2) {
    if(x1 > x2) swap(x1,x2);
    for(int i = x1; i <= x2; i++){
        m[i][y1] += 1;
    }
}

void diagDownVentLine(int m[SIZE][SIZE],int x1, int y1,int x2, int y2) {
    if(x1 >= x2){
        swap(x1,x2);
        swap(y1,y2);
    }
    for(int i = x1, j = y1; i <= x2 && j <= y2; i++, j++){
        m[i][j] += 1;
    }
}

void diagUpVentLine(int m[SIZE][SIZE], int x1,int y1,int x2,int y2) {
    if(x1 >= x2) {
        swap(x1,x2);
        swap(y1,y2);
    }
    for(int i = x1, j = y1; i <= x2 && j >= y2; i++, j--){
        m[i][j] += 1;
    }
}

void diagRestVentLine(int m[SIZE][SIZE], int x1,int y1,int x2,int y2){
    if(x1 >= x2){
        swap(x1,x2);
        swap(y1,y2);
    }
    if(y1 >= y2){
        diagUpVentLine(m,x1,y1,x2,y2);
    }else{
        diagDownVentLine(m,x1,y1,x2,y2);
    }
}

void part1() {
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;

    vector<Ventline> ventlines;
    while(getline(input,line)){
        int x1,y1,x2,y2;
        fromline(&x1,&y1,&x2,&y2, line);

        Ventline v = Ventline(x1,y1,x2,y2);
        ventlines.push_back(v);
    }
    input.close();

    memset(&map,0,sizeof(int)*SIZE*SIZE);
    
    for(Ventline v : ventlines){
        int x1 = v.start().getX();
        int y1 = v.start().getY();
        int x2 = v.end().getX();
        int y2 = v.end().getY();
        
        if (x1 == x2) {
            verticalVentLine(map, x1,y1,y2);
        }
        else if (y1 == y2) {
            horizontalVentLine(map, y1, x1,x2);
        }
    }

    int count = 0;
    for(int j = 0; j < SIZE; j++){
        for(int i = 0; i < SIZE; i++){
            if(map[i][j] > 1) count++;
        }
    }
    cout << "part1: " << count << endl;
}

void part2() {
    ifstream input(INPUT);
    if(input.fail()) return;

    string line;
    vector<Ventline> ventlines;
    while(getline(input,line)){
        int x1,y1,x2,y2;
        fromline(&x1,&y1,&x2,&y2, line);

        Ventline v = Ventline(x1,y1,x2,y2);
        ventlines.push_back(v);
    }
    input.close();

    memset(&map,0,sizeof(int)*SIZE*SIZE);
    
    for(Ventline v : ventlines){
        int x1 = v.start().getX();
        int y1 = v.start().getY();
        int x2 = v.end().getX();
        int y2 = v.end().getY();
        
        if (x1 == x2) {
            verticalVentLine(map, x1,y1,y2);
        }
        else if (y1 == y2) {
            horizontalVentLine(map, y1, x1,x2);
        }
        else if(x1 == y1 && x2 == y2){
            diagDownVentLine(map, x1,y1,x2,y2);
        }
        else if(x1 == y2 && y1 == x2){
            diagUpVentLine(map, x1,y1,x2,y2);
        }
        else {
            diagRestVentLine(map,x1,y1,x2,y2);
        }
    }

    fstream fout;
    if(!fout.fail()){
        fout.open("map.csv", ios::out);
        int count = 0;
        for(int j = 0; j < SIZE; j++){
            for(int i = 0; i < SIZE; i++){
                if(map[i][j] == 0) fout << " .";
                else fout << " " << map[i][j];
                if(map[i][j] > 1) count++;
            }
            fout << endl;
        }
        fout.close();
        cout << "part2: " << count << endl;
    }else return;
}

int main(){
    part1();
    part2();
    return 0;
}