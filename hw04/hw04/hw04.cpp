//
//  hw04.cpp
//  hw04
//  Helal Chowdhury

//  Created by Helal Chowdhury on 2/26/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior {
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
public:
    Noble(const string& name) : name(name) {};
    // Returns the noble's army
    vector<Warrior*> getArmy() const {
        return army;
    }
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
            cout << warrior.getName() << ", you're fired! -- " << name << endl;
            return true;
        }
        cerr << name << " cannot fire " << warrior.getName() << ". He is not employed by him." << endl;
        return false;
    }
    // Takes in a noble and simulates a battle
    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        double totalStrength = 0;
        double opponentTotalStrength = 0;
        vector<Warrior*> opponentArmy = opponent.getArmy();
        // Loops through the army and gets its total strength
        for (size_t i = 0; i < army.size(); ++i) {
            totalStrength += army[i]->getStrength();
        }
        // Loops through the opponent's army and gets its total strength
        for (size_t i = 0; i < opponentArmy.size(); ++i) {
            opponentTotalStrength += opponentArmy[i]->getStrength();
        }
        if (dead && opponent.dead) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (dead) {
            cout << "He's dead " << opponent.name << endl;
        }
        else if (opponent.dead) {
            cout << "He's dead " << name << endl;
        }
        else if (totalStrength == opponentTotalStrength) {
            // Loops through the army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->loseStrength(0);
            }
            // Loops through the opponent's army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < opponentArmy.size(); ++i) {
                opponentArmy[i]->loseStrength(0);
            }
            dead = true;
            opponent.dead = true;
            cout << "Mutual Annihalation: " << name << " and " << opponent.getName() << " die at each other's hands." << endl;
        }
        else if (totalStrength > opponentTotalStrength) {
            // Loops through the army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < opponentArmy.size(); ++i) {
                opponentArmy[i]->loseStrength(0);
                opponent.dead = true;
            }
            double strengthRatio = 1 - (opponentTotalStrength / totalStrength);
            // Loops through the opponent's army and reduces each warrior's strength by the ratio of the opponent army's strength to the army's strength
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->loseStrength(strengthRatio);
            }
            cout << name << " defeats " << opponent.name << endl;
        }
        else if (totalStrength < opponentTotalStrength) {
            // Loops through the army and makes each warrior's strength equal to 0
            for (size_t i = 0; i < army.size(); ++i) {
                army[i]->loseStrength(0);
                dead = true;
            }
            double strengthRatio = 1 - (totalStrength / opponentTotalStrength);
            // Loops through the army and reduces each warrior's strength by the ratio of the army's strength to the opponent's army's strength
            for (size_t i = 0; i < opponentArmy.size(); ++i) {
                opponentArmy[i]->loseStrength(strengthRatio);
            }
            cout << opponent.name << " defeats " << name << endl;
        }
    }
    // Displays all nobles, along with their warrior's names and strengths
    void display() {
        cout << name << " has an army of " << army.size() << endl;
        for (size_t i = 0; i < army.size(); ++i) {
            cout << "        " << army[i]->getName() << ": " << army[i]->getStrength() << endl;
        }
    }
private:
    string name;
    vector<Warrior*> army;
    bool dead = false;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah);
    art.display();
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    
    
    // NEW OUTPUT CODE
    cout << "==========\n"
    << "Status after all battles, etc.\n";
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
}
