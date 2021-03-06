#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define INPUT "./input.txt"

//P1/P2 COMMENTS (can be found at lines 202..240):
//P1: remove line comment for pt1
//     & add line comment for pt2

//P2: remove line comment for pt2
//     & add line comment for pt1

class Board{
private:
    struct number {
        int value;
        bool marked;
    };
    number numbers[5][5];
    int id;
    static int boardID;
    bool won = false;
public:
    //CONSTRUCTOR
    Board(){ 
        id = ++boardID;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                numbers[i][j].value = 0;
                numbers[i][j].marked = false;
            }
        }
    }
    
    //GETTERS
    int getValue(int i, int j){
        return numbers[i][j].value;
    }

    bool isNumMarked(int i, int j){
        return numbers[i][j].marked;
    }

    int getID(){
        return id;
    }

    //SETTERS
    void setNumMarked(int n){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(getValue(i,j) == n){
                    numbers[i][j].marked = true;
                    break;
                }
            }
        }
        won = check();
    }

    void setValue(int i, int j, int v){
        numbers[i][j].value = v;
    }

    //class FUNCTIONS

    bool check(){
        for(int sor = 0; sor < 5; sor++){
            int counter = 0;
            for(int oszlop = 0; oszlop < 5; oszlop++){
                if(isNumMarked(sor,oszlop)) counter++;
            }
            if(counter == 5) return true;
        }

        for(int sor = 0; sor < 5; sor++){
            int counter = 0;
            for(int oszlop = 0; oszlop < 5; oszlop++){
                if(isNumMarked(oszlop,sor)) counter++;
            }
            if(counter == 5) return true;
        }
        return false;
    }

    bool wonGame(){
        return won;
    }

    void toString(){
        cout << "BOARD " << id << endl;
        cout << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << " " << (isNumMarked(i,j) ? "<"+ to_string(getValue(i,j)) +">" : to_string(getValue(i,j)));
            }
            cout << endl;
        }
    }
};
int Board::boardID = 0;

vector<int> storeFirstLine(ifstream *input){
    string l;
    *input >> l;

    vector<int> guesses;
    int i = 0;
    string res;
    while (i < l.length()) {
        res = "";
        int j = i;
        while (l[j] != ',' && j < l.length()) {
            res += l[j++];
            i = j;
        }
        if (res.length() != 0) {
            guesses.push_back(stoi(res));
            i++;
            res = "";
        }
    }
    return guesses;
}

vector<int> storeLine( string l){
    vector<int> guesses;
    int i = 0;
    string res;

    while (i < l.length()) {
        res = "";
        while(l[i] == ' '){
            i++;
        }
        
        int j = i;
        while (l[j] != ' ' && j < l.length()) {
            res += l[j++];
        }
        guesses.push_back(stoi(res));
        if (i != j ) i = j;
        else i++;
    }
    return guesses;
}

vector<Board> storeBoards(ifstream* input) {
    string l;
    vector<Board> res;
    int i = 0;
    Board b = Board();

    while(getline(*input, l)){
        if (l.length() > 0){
            vector<int> line = storeLine(l);
            int j = 0;
            while(j < 5){
                b.setValue(i,j,line[j]);
                j++;
            }
            i++;
        }else {
            if(i == 5) {
                res.push_back(b);
                b = Board();
                i = 0;
            }
        }
    }
    res.push_back(b);
    return res;
}

void part1(){
    ifstream input(INPUT);
    if(input.fail()) return;

    vector<int> guesses;
    guesses = storeFirstLine(&input);

    vector<Board> boards;
    boards = storeBoards(&input);
    
    int round = 1;
    int n;
    Board w;

    bool winner = false;
    while(!winner){
        n = guesses[round-1];
        int b = 0;
        while(b < boards.size()){
            boards[b].setNumMarked(n);

            if(boards[b].wonGame()){
                w = boards[b];
                winner = true;
            }
            b++;
        }
        round++;
    }
    
    cout << "---------part1---------" <<endl;
    cout << "BINGO!!!! THE WINNER IS ";
    w.toString();
    
    int sum = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(!w.isNumMarked(i,j)) sum += w.getValue(i,j);
        }
    }
    cout << "Sum of all unmarked numbers: " << sum << endl;
    cout << "Last number called: " << n << endl;
    cout << "FINAL SCORE: " << sum << "*" << n << "=" << sum * n << endl;

    input.close();
}

void part2(){
    ifstream input(INPUT);
    if(input.fail()) return;

    vector<int> guesses;
    guesses = storeFirstLine(&input);

    vector<Board> boards;
    boards = storeBoards(&input);

    int round = 1;
    int n;
    Board w;

    while(boards.size() > 0){
        n = guesses[round-1];
        int b = 0;
        while(b < boards.size()){
            boards[b].setNumMarked(n);

            if(boards[b].wonGame()){
                w = boards[b];
                boards.erase(boards.begin()+b);
                b--;
            }
            b++;
        }
        round++;
    }

    cout << "------------part2------------" << endl;
    cout << "THE VERY LAST WINNER BOARD IS ";
    w.toString();
    
    int sum = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(!w.isNumMarked(i,j)) sum += w.getValue(i,j);
        }
    }
    cout << "Sum of all unmarked numbers: " << sum << endl;
    cout << "Last number called: " << n << endl;
    cout << "FINAL SCORE: " << sum << "*" << n << "=" << sum * n << endl;

    input.close();
}

int main(){
    part1();
    part2();
    return 0;
}