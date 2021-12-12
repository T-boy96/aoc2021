#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define INPUT "./input.txt"
#define NF string::npos //no matches found with std::string::find()

string segments = "       ";  //each value on i=0..7 will be a segment going from the top to bottom and left to right

void digitsFromString(size_t pos, string digits, vector<string> &numbers){
    string digit;
    
    while((pos = digits.find(" ")) != NF){
        digit = digits.substr(0, pos);
        if(digit.length() != 0) {
            numbers.push_back(digit);
        } 
        digits.erase(0, pos + 1);
    }
    
    if(digits.length() != 0){
        numbers.push_back(digits);
    }
}

int digitsWithUniqueLength(string digits,size_t pos){
    int res = 0;
    vector<string> numbers;
    digitsFromString(pos, digits,numbers);

    for(int i = 0; i < numbers.size(); i++){
        int l = numbers[i].size();
        if( l == 2 || l == 3 || l == 4 || l == 7) res++;
    }
    numbers.clear();
    return res;
}

void part1() {
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    string delim = "|";

    int count = 0;
    while(getline(input,line)) {
        string digits = line.substr(line.find(delim) + 2,line.length());
        count += digitsWithUniqueLength(digits,0);
    }
    input.close();

    cout << "part1: " << count << endl;
}

char seg0(string one, string seven){
    for(char c : seven){
        if (one.find(c) == NF) return c;
    }
}

void seg1346(string one, string four, string seven, string eight, vector<string> zeroSixNine){
    string notInZero = "";  // two characters from segments: one is not in 0
    string notInNine = "";  // two characters from segments: one is not in 9
    for(string s : zeroSixNine){
        for(char c : s){
            if( four.find(c) != NF && seven.find(c) == NF && notInZero.find(c) == NF) {
                notInZero += c;
            }

            else if( four.find(c) == NF && seven.find(c) == NF && notInNine.find(c) == NF ) {
                notInNine += c;
            }
        }
    }

    for(char c : notInZero){
        if( zeroSixNine[0].find(c) != NF && zeroSixNine[1].find(c) != NF && zeroSixNine[2].find(c) != NF ) {
            segments[1] = c;
        }else segments[3] = c;
    }

    for(char c : notInNine){
        if( zeroSixNine[0].find(c) == NF || zeroSixNine[1].find(c) == NF || zeroSixNine[2].find(c) == NF ) {
            segments[4] = c;
        }else segments[6] = c;
    }
}

char seg25(string one, string four, string seven, string eight, vector<string> twoThreeFive, vector<string> zeroSixNine){
    string s = "abcdefg";
    for(int i = 0; i < s.length(); i++){
        if( one.find(s[i]) != NF &&
            zeroSixNine[0].find(s[i]) != NF && zeroSixNine[1].find(s[i]) != NF && zeroSixNine[2].find(s[i]) != NF){
            segments[5] = s[i];
            break;
        }
    }
    
    for(char c : s){
        if(segments.find(c) == NF) segments[2] = c;
    }
}

void findSegments(vector<string> patterns){
    char zero[6];
    string one;
    char two[5];
    char three[5];
    string four;
    char five[5];
    string six;
    string seven;
    string eight;
    char nine[6];
    
    vector<string> zeroSixNine;
    vector<string> twoThreeFive;
    
    for(string p : patterns){
        int l = p.length();
        switch(l){
            case 2:
                one = p;
                break;
            case 3:
                seven = p;
                break;
            case 4:
                four = p;
                break;
            case 5:
                twoThreeFive.push_back(p);
                break;
            case 6:
                zeroSixNine.push_back(p);
                break;
            case 7:
                eight = p;
                break;
        }
    }
    //segment 0
    segments[0] = seg0(one,seven);
    //segments 1, 3, 4, 6
    seg1346(one,four,seven,eight, zeroSixNine);
    //segments 2, 5
    seg25(one,four,seven,eight, twoThreeFive,zeroSixNine);
}

int findDigits(vector<string> sdigits){
    string res = "";    //decoded 4 digit result at the end

    //numbers with segments' indexes
    string one =   "25";
    string seven = "025";
    string four =  "1235";
    string eight = "0123456";
    
    string two =   "02346";
    string three = "02356";
    string five =  "01356";

    string zero =  "012456";
    string nine =  "012356";
    string six =   "013456";
    for (int i = 0; i < sdigits.size(); i++){
        string num = sdigits[i];

        //1 4 7 8
        if(num.length() == one.length()) res+= "1";
        else if(num.length() == seven.length()) res += "7";
        else if(num.length() == four.length()) res += "4";
        else if(num.length() == eight.length()) res += "8";
        
        //2 3 5
        else if(num.length() == 5){
            string n = "";
            for(int j = 0; j < num.length(); j++){
                char c = num[j];
                for(int k = 0; k < segments.length(); k++){
                    if(c == segments[k]) {
                        if(two.find(to_string(k)) != NF && three.find(to_string(k)) == NF && five.find(to_string(k)) == NF){
                            n = "2";
                            break;
                        }else if (two.find(to_string(k)) == NF && three.find(to_string(k)) == NF && five.find(to_string(k)) != NF){
                            n = "5";
                            break;
                        }
                    }
                }
            }
            res += n;
            if(n == "") res += "3";
        }

        //0 6 9
        else {
            string zeroSix;
            string sixNine;
            string zeroNine;
            for(int j = 0; j < num.length(); j++) {
                char c = num[j];
                for(int k = 0; k < segments.length(); k++){
                    if (c == segments[k] && i == res.length()){
                        if(nine.find(to_string(k)) == NF && zeroSix.length() < 1 ){
                            zeroSix += to_string(k);
                            if(zeroNine.length() > 0) {res += "0"; break;}
                            else if(sixNine.length() > 0) {res += "6"; break;}
                        }
                        else if(zero.find(to_string(k)) == NF && sixNine.length() < 1) {
                            sixNine += to_string(k);
                            if(zeroNine.length() > 0) {res += "9"; break;}
                            else if(zeroSix.length() > 0) {res += "6"; break;}
                        }
                        else if (six.find(to_string(k)) == NF && zeroNine.length() < 1) {
                            zeroNine += to_string(k);
                            if(sixNine.length() > 0) {res += "9"; break;}
                            else if(zeroSix.length() > 0) {res += "0"; break;}
                        }
                    }
                }
            }
        }
    }
    return stoi(res);
}

void print(vector<string> vector, const string message){
    cout << message;
    for(string s : vector) cout << " " << s << ",";
    cout << endl;
}

void printSegments() {
    cout << "segments: " << endl;
    cout << " " << segments[0] << segments[0] << segments[0] << segments[0] << endl;
    cout << segments[1] << "    "<< segments[2] << endl;
    cout << segments[1] << "    "<< segments[2] << endl;
    cout << " " << segments[3] << segments[3] << segments[3] << segments[3] << endl;
    cout << segments[4] << "    "<< segments[5] << endl;
    cout << segments[4] << "    "<< segments[5] << endl;
    cout << " " << segments[6] << segments[6] << segments[6] << segments[6] << endl;
}

void part2() {
    ifstream input(INPUT);
    if(input.fail()) return;
    string line;
    string delim = "|";
    
    vector<string> signalPatterns;
    vector<string> digits;

    long int sum = 0;
    while(getline(input,line)) {
        string firstHalf = line.substr(0, line.find(delim));
        digitsFromString(0, firstHalf, signalPatterns);
        
        string secondHalf = line.substr(line.find(delim) + 2,line.length());
        digitsFromString(0, secondHalf, digits);
        
        findSegments(signalPatterns);

        // print(signalPatterns, "  signal patterns (codes):  ");
        // print(digits, "digits to decode in order:  ");
        // printSegments();

        int value = findDigits(digits);
        sum += value;
        
        // cout << "  value of decoded digits:   "<< value << endl;
        // cout << endl;
        
        signalPatterns.clear();
        digits.clear();
    }
    input.close();
    cout << "part2: " << sum << endl;
}

int main(){
    part1();
    part2();
    return 0;
}