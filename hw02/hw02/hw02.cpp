//
//  hw02.cpp
//  hw02
//  Helal Chowdhury

//  Created by Helal Chowdhury on 2/6/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Warrior{
    string name;
    int strength;
};

void addWarrior(ifstream& text, vector<Warrior>& warriors);
void printStatus(const vector<Warrior>& warriors);
void battle(ifstream& text, vector<Warrior>& warriors);

// Opens file and reads commands from file
int main() {
    vector<Warrior> warriors;
    string command;
    ifstream text("warriors.txt");
    
    if (!text) {
        cerr << "failed to open warriors text file";
        exit(1);
    }
    
    while (text >> command) {
        if(command == "Warrior") {
            addWarrior(text, warriors);
        }
        else if(command == "Status") {
            printStatus(warriors);
        }
        else {
            battle(text, warriors);
        }
    }
    text.close();
}

// Creates and adds warrior object into vector of warrios
void addWarrior(ifstream& text, vector<Warrior>& warriors) {
    Warrior warriorNew;
    text >> warriorNew.name >> warriorNew.strength;
    warriors.push_back(warriorNew);
}

// Prints the current warriors and their strength
void printStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); ++i) {
        cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].strength << endl;
    }
}

// Makes 2 warriors fight if possible, and adjusts the current strength level
void battle(ifstream& text, vector<Warrior>& warriors) {
    string name1;
    string name2;
    int first;
    int second;
    
    text >> name1 >> name2;
    cout << name1 << " battles " << name2 << endl;
    
    for(int i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name1) {
            first = i;
        }
        if (warriors[i].name == name2) {
            second = i;
        }
    }
    
    if(warriors[first].strength == warriors[second].strength){
        if(warriors[second].strength == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else{
            warriors[second].strength = 0;
            warriors[first].strength = 0;
            cout << "Mutual Annihilation: " << name1 << " and " << name2
            << " die at each other's hands" << endl;
        }
    }
    else if(warriors[first].strength > warriors[second].strength){
        if(warriors[second].strength == 0) {
            cout << "He's dead, " << name1 << endl;
        }
        else{
            int strength  = warriors[second].strength;
            warriors[second].strength = 0;
            warriors[first].strength -= strength;
            cout << name1 << " beats " << name2 << endl;
        }
    }
    else if(warriors[first].strength < warriors[second].strength){
        if(warriors[first].strength == 0) {
            cout << "He's dead " << name2 << endl;
        }
        else{
            int strength = warriors[first].strength;
            warriors[first].strength = 0;
            warriors[second].strength -= strength;
            cout << name2 << " beats " << name1 << endl;
        }
    }
}
