//
//  hw03.cpp
//  hw03
//  Helal Chowdhury

//  Created by Helal Chowdhury on 2/12/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior {
public:
    Warrior(const string& name, const string& wName, int strength) : warriorName(name), weapon(wName, strength){}
    void displayWarrior() const { // Prints Warrior name and calls function to print weapon name and strengtth
        cout << "Warrior: " << warriorName << ", ";
        weapon.displayWeapon();
    }
    string getName() const {
        return warriorName;
    }
    
    int getStrength() const {
        return weapon.getWeaponStrength();
    }
    
    void setStrength(int strengthNew) {
        weapon.weaponDamage(strengthNew);
    }
    
private:
    class Weapon {
    public:
        Weapon(const string& name, int wStrength) : weaponName(name), strength(wStrength) {}
        void displayWeapon() const { // Prints weapon name and strength
            cout << "weapon: " << weaponName << ", " << strength << endl;
        }
        
        int getWeaponStrength() const {
            return strength;
        }
        
        void weaponDamage(int strengthNew) {
            strength = strengthNew;
        }
        
    private:
        string weaponName;
        int strength;
    };
    string warriorName;
    Weapon weapon;
};


void addWarrior(ifstream& text, vector<Warrior>& warriors);
void printStatus(const vector<Warrior>& warriors);
void battle(ifstream& text, vector<Warrior>& warriors);

// Opens file and reads commands from file
int main() {
    vector<Warrior> warriors;
    string command;
    ifstream text("warriorNew.txt");
    
    if (!text) {
        cerr << "failed to open warriors text file" << endl;
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
    string name;
    string weaponName;
    int strength;
    text >> name >> weaponName >> strength;
    Warrior warriorNew(name, weaponName, strength);
    warriors.push_back(warriorNew);
}

// Prints the current warriors and their strength
void printStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); ++i) {
        warriors[i].displayWarrior();
    }
}

// Makes 2 warriors fight if possible, and adjusts the current weapon strength level
void battle(ifstream& text, vector<Warrior>& warriors) {
    string name1;
    string name2;
    int first;
    int second;
    
    text >> name1 >> name2;
    cout << name1 << " battles " << name2 << endl;
    
    for(int i = 0; i < warriors.size(); i++) {
        if (warriors[i].getName() == name1) {
            first = i;
        }
        if (warriors[i].getName() == name2) {
            second = i;
        }
    }
    
    if(warriors[first].getStrength() == warriors[second].getStrength()){
        if(warriors[second].getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else{
            warriors[second].setStrength(0);
            warriors[first].setStrength(0);
            cout << "Mutual Annihilation: " << name1 << " and " << name2
            << " die at each other's hands" << endl;
        }
    }
    else if(warriors[first].getStrength() > warriors[second].getStrength()){
        if(warriors[second].getStrength() == 0) {
            cout << "He's dead, " << name1 << endl;
        }
        else{
            int strengthNew  = warriors[first].getStrength() - warriors[second].getStrength();
            warriors[second].setStrength(0);
            warriors[first].setStrength(strengthNew);
            cout << name1 << " beats " << name2 << endl;
        }
    }
    else if(warriors[first].getStrength() < warriors[second].getStrength()){
        if(warriors[first].getStrength() == 0) {
            cout << "He's dead " << name2 << endl;
        }
        else{
            int strengthNew = warriors[second].getStrength() - warriors[first].getStrength();
            warriors[first].setStrength(0);
            warriors[second].setStrength(strengthNew);
            cout << name2 << " beats " << name1 << endl;
        }
    }
}

