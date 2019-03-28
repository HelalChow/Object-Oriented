//
//  hw05.cpp
//  hw05
//  Helal Chowdhury

//  Created by Helal Chowdhury on 3/7/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior {
    friend ostream& operator<<(ostream& os, Warrior& warrior){
        os << warrior.name << ": " << warrior.strength << endl;
        return os;
    }
public:
    Warrior(const string& name, int strength) : name(name), strength(strength) {};
    // Checks to see if the warrior is employed
    bool isHired() const {
        return hired;
    }
    // Checks to see if the warrior is dead
    bool isDead() const {
        return dead;
    }
    // Returns the warrior's name
    string getName() const {
        return name;
    }
    // Returns the warrior's strength
    int getStrength() const {
        return strength;
    }
    // Changes the warrior's strength
    void loseStrength(double strengthRatio) {
        strength = strength * strengthRatio;
    }
    // Changes the warrior's "hired" status to true
    void hire() {
        hired = true;
    }
    // Changes the warrior's "hired" status to false
    void fire() {
        hired = false;
    }
    // Changes the warrior's "dead" status to true
    void die() {
        dead = true;
    }
private:
    string name;
    int strength;
    bool hired = false;
    bool dead = false;
};

class Noble {
    friend ostream& operator<<(ostream& os, Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for(size_t i = 0; i < noble.army.size(); i++){
            os << "\t" << *noble.army[i];
        }
        return os;
    }
public:
    Noble(const string& name) : name(name) {};
    // Returns the noble's name
    string getName() const {
        return name;
    }
    // Takes in a warrior and places him into the noble's army
    bool hire(Warrior& warrior) {
        if (!dead) {
            if (warrior.isHired() || warrior.isDead()) {
                cerr << "Warrior is either dead or already employed." << endl;
                return false;
            }
            army.push_back(&warrior);
            warrior.hire();
            totalStrength += warrior.getStrength();
            return true;
        }
        cerr << "Noble is dead" << endl;
        return false;
    }
    // Takes in a warrior and removes him from the noble's army
    bool fire(Warrior& warrior) {
        int new_i = -1;
        // Loops through the army to see if the warrior is already employed
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &warrior) {
                new_i = i;
                break;
            }
        }
        if (new_i >= 0) {
            // Loops through the army and alters it to remove the warrior
            for (new_i; new_i < army.size() - 1; ++new_i) {
                army[new_i] = army[new_i + 1];
            }
            army.pop_back();
            warrior.fire();
            cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << endl;
            return true;
        }
        cerr << name << " cannot fire " << warrior.getName() << ". He is not employed by him." << endl;
        return false;
    }
    // Takes in a noble and simulates a battle
    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (dead && opponent.dead) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (dead) {
            cout << "He's dead " << opponent.name << endl;
        }
        else if (opponent.dead) {
            cout << "He's dead " << name << endl;
        }
        else if (totalStrength == opponent.totalStrength) {
            // Loops through the army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->loseStrength(0);
            }
            // Loops through the opponent's army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < opponent.army.size(); ++i) {
                opponent.army[i]->loseStrength(0);
            }
            dead = true;
            opponent.dead = true;
            cout << "Mutual Annihalation: " << name << " and " << opponent.getName() << " die at each other's hands." << endl;
        }
        else if (totalStrength > opponent.totalStrength) {
            // Loops through the army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < opponent.army.size(); ++i) {
                opponent.army[i]->loseStrength(0);
                opponent.dead = true;
            }
            double strengthRatio = 1 - (opponent.totalStrength / totalStrength);
            // Loops through the opponent's army and reduces each warrior's strength by the ratio of the opponent army's strength to the army's strength
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->loseStrength(strengthRatio);
            }
            cout << name << " defeats " << opponent.name << endl;
        }
        else if (totalStrength < opponent.totalStrength) {
            // Loops through the army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->loseStrength(0);
                dead = true;
            }
            double strengthRatio = 1 - (totalStrength / opponent.totalStrength);
            // Loops through the army and reduces each warrior's strength by the ratio of the army's strength to the opponent's army's strength
            for (size_t i = 0; i < opponent.army.size(); ++i) {
                opponent.army[i]->loseStrength(strengthRatio);
            }
            cout << opponent.name << " defeats " << name << endl;
        }
    }
private:
    string name;
    double totalStrength = 0;
    vector<Warrior*> army;
    bool dead = false;
};


void createNoble(ifstream& text, vector<Noble*>& noblePtr);
void createWarrior(ifstream& text, vector<Warrior*>& warriorPtr);
size_t nobleIndex(const string& name, const vector<Noble*>& noblePtr);
size_t warriorIndex(const string& name, const vector<Warrior*>& warriorPtr);
bool hireWarrior(ifstream& text, const vector<Noble*>& noblePtr, const vector<Warrior*>& warriorPtr);
bool fireWarrior(ifstream& text, const vector<Noble*>& noblePtr, const vector<Warrior*>& warriorPtr);
void printStatus(const vector<Noble*>& noblePtr, const vector<Warrior*>& warriorPtr);
bool battle(ifstream& ifs, vector<Noble*>& nobles);
void clearNobles(vector<Noble*>& nobles);
void clearWarriors(vector<Warrior*>& warriors);


int main() {
    ifstream text("nobleWarriors.txt");
    if(!text){
        cerr << "Failed to open the nobleWarriors text file";
        exit(1);
    }
    
    vector<Noble*> noblePtr;
    vector<Warrior*> warriorPtr;
    
    
    string command;
    while(text >> command){
        if (command == "Noble"){
            createNoble(text, noblePtr);
        }
        else if(command == "Warrior") {
            createWarrior(text, warriorPtr);
        }
        else if(command == "Hire") {
            hireWarrior(text, noblePtr, warriorPtr);
        }
        else if(command == "Fire") {
            fireWarrior(text, noblePtr, warriorPtr);
        }
        else if(command == "Clear") {
            clearNobles(noblePtr);
            clearWarriors(warriorPtr);
        }
        else if(command == "Battle") {
            battle(text, noblePtr);
        }
        else{
            printStatus(noblePtr, warriorPtr);
        }
    }
    text.close();
}

void createNoble(ifstream& text, vector<Noble*>& noblePtr){
    string name;
    text >> name;
    bool alreadyExists = false;
    for (size_t i = 0; i < noblePtr.size(); ++i) {
        if (noblePtr[i]->getName() == name) {
            alreadyExists = true;
        }
    }
    if(!alreadyExists){
        noblePtr.push_back(new Noble(name));
    }
    else{
        cerr << name << " already exists" << endl;
    }
}

void createWarrior(ifstream& text, vector<Warrior*>& warriorPtr){
    string name;
    int strength;
    text >> name >> strength;
    bool alreadyExists = false;
    for (size_t i = 0; i < warriorPtr.size(); ++i) {
        if (warriorPtr[i]->getName() == name) {
            alreadyExists = true;
        }
    }
    if(!alreadyExists){
        warriorPtr.push_back(new Warrior(name, strength));
    }
    else{
        cerr << name << " already exists" << endl;
    }
}

size_t nobleIndex(const string& name, const vector<Noble*>& noblePtr){
    for(size_t i = 0; i < noblePtr.size(); i++){
        if(noblePtr[i]->getName() == name){
            return i;
        }
    }
    return -1;
}

size_t warriorIndex(const string& name, const vector<Warrior*>& warriorPtr){
    for(size_t i = 0; i < warriorPtr.size(); i++){
        if(warriorPtr[i]->getName() == name){
            return i;
        }
    }
    return -1;
}

bool hireWarrior(ifstream& text, const vector<Noble*>& noblePtr, const vector<Warrior*>& warriorPtr) {
    string nobleName;
    string warriorName;
    text >> nobleName >> warriorName;
    size_t indexNoble = nobleIndex(nobleName, noblePtr);
    size_t indexWarrior = warriorIndex(warriorName, warriorPtr);
    if (indexNoble == -1){
        cerr << "Noble " << nobleName << " does not exist" << endl;
        return false;
    }
    else if(indexWarrior == -1) {
        cerr << "Warrior " << warriorName << " does not exist" << endl;
        return false;
    }
    else{
        return noblePtr[indexNoble]->hire(*warriorPtr[indexWarrior]);
    }
}

bool fireWarrior(ifstream& text, const vector<Noble*>& noblePtr, const vector<Warrior*>& warriorPtr) {
    string nobleName;
    string warriorName;
    text >> nobleName >> warriorName;
    size_t indexNoble = nobleIndex(nobleName, noblePtr);
    size_t indexWarrior = warriorIndex(warriorName, warriorPtr);
    if (indexNoble == -1){
        cerr << "Noble " << nobleName << " does not exist" << endl;
        return false;
    }
    else if(indexWarrior == -1) {
        cerr << "Warrior " << warriorName << " does not exist" << endl;
        return false;
    }
    else{
        return noblePtr[indexNoble]->fire(*warriorPtr[indexWarrior]);
    }
}

void printStatus(const vector<Noble*>& noblePtr, const vector<Warrior*>& warriorPtr){
    int countNobles = 0;
    cout << "Status" << endl << "======" << endl << "Nobles: " << endl;
    for(size_t i = 0; i < noblePtr.size(); i++){
        cout << *noblePtr[i] << endl;
        countNobles += 1;
    }
    if(countNobles == 0){
        cout << "NONE" << endl;
    }
    cout << "Unemployed warriors:" << endl;
    int countUnemployed = 0;
    for(size_t i = 0; i < warriorPtr.size(); i++){
        if(!(warriorPtr[i]->isHired())){
            cout << "\t" << *warriorPtr[i] << endl;
            countUnemployed += 1;
        }
    }
    if(countUnemployed == 0){
        cout << "NONE" << endl;
    }
}

bool battle(ifstream& ifs, vector<Noble*>& nobles) {
    string nobleOne, nobleTwo;
    ifs >> nobleOne >> nobleTwo;
    size_t nobleOneIndex = nobleIndex(nobleOne, nobles);
    size_t nobleTwoIndex = nobleIndex(nobleTwo, nobles);
    if (nobleOneIndex == -1){
        cerr << "Noble " << nobleOne << " does not exist" << endl;
        return false;
    }
    else if(nobleTwoIndex == -1) {
        cerr << "Noble " << nobleTwo << " does not exist" << endl;
        return false;
    }
    else{
        nobles[nobleOneIndex]->battle(*nobles[nobleTwoIndex]);
        return true;
    }
}

void clearNobles(vector<Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        delete nobles[i];
    }
    nobles.clear();
}

void clearWarriors(vector<Warrior*>& warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        delete warriors[i];
    }
    warriors.clear();
}

