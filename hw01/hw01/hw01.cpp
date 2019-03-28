//
//  main.cpp
//  hw01
//  Decrypt the Ceaser Cypher

//  Created by Helal Chowdhury on 2/1/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//  Takes an encrypted character and return sdecrypted char
char decryptChar(char letter, int step){
    char newLetter;
    if (letter <= 'z' && letter >= 'a'){
        if(letter - step < 'a'){
            int count = 1;
            while (letter > 'a'){
                letter --;
                count ++;
            }
            newLetter = 'z' - (step - count);
        }
        else{
            newLetter = letter - step;
        }
        return newLetter;
    }
    return letter;
}

//  Takes a line from the encrypted text and decrypts the entire line
void decryptString(string& line, int step){
    for(int i = 0; i < line.size(); i++){
        line[i] = decryptChar(line[i], step);
    }
}

//  Prints the entire decrypted text
void printText(const vector<string>& newText){
    for(int i = newText.size() - 1; i >= 0; i--){
        cout << newText[i] << endl;
    }
}

//  Reads encrypted text and stores lines in vector of strings
int main(){
    ifstream text("encrypted.txt");
    if (!text) {
        cerr << "failed to open encrypted text" << endl;
        exit(1);
    }
    vector<string> newText;
    string line;
    string step;
    int number;
    getline(text, step);
    number = stoi(step);
    while (getline(text, line)) {
        newText.push_back(line);
    }
    for(int i = 0; i < newText.size(); i++){
        decryptString(newText[i], number);
    }
    printText(newText);
}


