#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include <sstream>

using namespace std;

#define INPUT "./input.txt"

//2D matrix
vector<vector <int>> map;

//lowpoints:
// [i][0] : row idx
// [i][1] : column idx
// [i][2] : value
vector<vector <int>> lowPoints;



void printMap(){
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[0].size(); j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

void findLowPoints(){
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[0].size(); j++) {
            int n = map[i][j];
            //felső oldal
            if(i == 0){
                //bal felső sarok
                if(j == 0){
                    if(map[i+1][j] > n && map[i][j+1] > n){
                        lowPoints.push_back({i,j,n});
                    }
                }
                //jobb felső sarok
                else if (j == map[i].size()-1){
                    if(map[i][j-1] > n && map[i+1][j] > n){
                        lowPoints.push_back({i,j,n});
                    }
                }
                //felső oldal többi része
                else{
                    if(map[i][j-1] > n && map[i][j+1] > n && map[i+1][j] > n){
                        lowPoints.push_back({i,j,n});
                    }
                }
            }
            //alsó oldal
            else if (i == map.size()-1){
                //bal alsó sarok
                if(j == 0){
                    if (map[i-1][j] > n && map[i][j+1] > n){
                        lowPoints.push_back({i,j,n});
                    }
                }
                //jobb alsó sarok
                else if(j == map[i].size()-1){
                    if(map[i][j-1] > n && map[i-1][j] > n){
                        lowPoints.push_back({i,j,n});
                    }
                }
                //alsó oldal többi része
                else{
                    if(map[i][j-1] > n && map[i][j+1] > n && map[i-1][j] > n){
                        lowPoints.push_back({i,j,n});
                    }
                }
            }
            //bal oldal sarkok nélkül
            else if(j == 0){
                if(map[i-1][j] > n && map[i+1][j] > n && map[i][j+1] > n){
                    lowPoints.push_back({i,j,n});
                }
            }
            //jobb oldal sarkok nélkül
            else if(j == map[i].size()-1){
                if(map[i-1][j] > n && map[i+1][j] > n && map[i][j-1] > n){
                    lowPoints.push_back({i,j,n});
                }
            }
            //belső elemek
            else{
                if(map[i-1][j] > n && map[i+1][j] > n && map[i][j-1] > n && map[i][j+1] > n){
                    lowPoints.push_back({i,j,n});
                }
            }
        }
    }
}

void printLowPoints(){
    cout << "Lowpoints: " << endl;
    for(int i = 0; i < lowPoints.size(); i++){
        cout << lowPoints[i][2] << " at (" << lowPoints[i][0] << "," << lowPoints[i][1] << ")" << endl;
    }
}

void part1() {
    ifstream input(INPUT);
    if(input.fail()) return;
    char v;
    vector<int> row;
    while(input.get(v)){
        string s = "";
        s += v;
        if (v != '\n') row.push_back(stoi(s));
        else { map.push_back(row); row.clear();}
    }
    map.push_back(row); 
    row.clear();
    
    input.close();

    findLowPoints();

    // printLowPoints();

    int result = lowPoints.size();
    for(int i = 0; i < lowPoints.size(); i++){
        result += lowPoints[i][2];
    }
    cout << "part1: " << result << endl;
}

//PART2

class Basin{
public:
    vector<vector <int>> locations;
};

vector<Basin> basins;

void mapBasin(Basin &b, char d, int i, int j){
    for(vector<int> l : b.locations){
        if(l[0] == i && l[1] == j) return;
    }
    if (d == 'u'){
        if(i < 0) return;
        if(map[i][j] > map[i+1][j] && map[i][j] < 9 ){
            b.locations.push_back({i,j});
            mapBasin(b,'u', i-1,j);
            mapBasin(b,'l',i,j-1);
            mapBasin(b,'r',i,j+1);
        }
    }
    else if (d == 'r'){
        if(j > map[i].size()-1) return;
        if(map[i][j] > map[i][j-1] && map[i][j] < 9){
            b.locations.push_back({i,j});
            mapBasin(b,'r',i,j+1);
            mapBasin(b,'u',i-1,j);
            mapBasin(b,'d',i+1,j);
        }
    }
    else if (d == 'd'){
        if(i > map.size()-1) return;
        if(map[i][j] > map[i-1][j] && map[i][j] < 9){
            b.locations.push_back({i,j});
            mapBasin(b,'d',i+1,j);
            mapBasin(b,'l',i,j-1);
            mapBasin(b,'r',i,j+1);
        }
    }
    else if (d == 'l'){
        if(j < 0) return;
        if(map[i][j] > map[i][j+1] && map[i][j] < 9){
            b.locations.push_back({i,j});
            mapBasin(b,'l',i,j-1);
            mapBasin(b,'u',i-1,j);
            mapBasin(b,'d',i+1,j);
        }
    }
}

void findBasins(){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            for(vector<int> lp : lowPoints){
                if( i == lp[0] && j == lp[1] ){
                    Basin b;
                    b.locations.push_back(lp);
                    mapBasin(b, 'l', i, j-1);
                    mapBasin(b, 'r', i, j+1);
                    mapBasin(b, 'd', i+1, j);
                    mapBasin(b, 'u', i-1, j);
                    basins.push_back(b);
                }
            }
        }
    }
}

void printBasins(){
    int count = 0;
    for(Basin b : basins){
        cout << "Basin " << ++count << " (size " << b.locations.size() << "):";
        for(vector<int> l : b.locations){
            cout << "(" << l[0] << "," << l[1] << "), ";
        }
        cout << endl;
    }
}

void part2() {
    map.clear();
    ifstream input(INPUT);
    if(input.fail()) return;
    char v;
    vector<int> row;
    while(input.get(v)){
        string s = "";
        s += v;
        if (v != '\n') row.push_back(stoi(s));
        else { map.push_back(row); row.clear();}
    }
    map.push_back(row);
    row.clear();
    
    input.close();

    lowPoints.clear();
    findLowPoints();

    findBasins();

    // printBasins();
    
    while(basins.size() > 3){
        Basin min = basins[0];
        int idx = 0;
        for(int i = 0; i < basins.size(); i++){
            if(basins[i].locations.size() < min.locations.size()) { min = basins[i]; idx = i;}
        }
        basins.erase(basins.begin()+idx);
    }
    
    
    int result = 1;
    
    for(Basin b :basins){
        // cout << b.locations.size() << endl;
        result *= b.locations.size();
    }
    basins.clear();

    cout << "part2: " << result << endl;
}

int main() {
    part1();
    part2();
    return 0;
}