//
//  Warrior.hpp
//  hw06
//
//  Created by Helal Chowdhury on 3/25/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <string>

#ifndef WARRIOR_H
#define WARRIOR_H
namespace WarriorCraft {
    class Noble;
    
    class Warrior {
        friend std::ostream& operator<<(std::ostream&, const Warrior&);
    public:
        Warrior(const std::string&, int);
        // Checks to see if the warrior is employed
        bool isHired() const;
        // Checks to see if the warrior is dead
        bool isDead() const;
        // Returns the warrior's name
        std::string getName() const;
        // Returns the warrior's strength
        int getStrength() const;
        // Changes the warrior's strength
        void loseStrength(double);
        // Changes the warrior's "boss" member variable to the parameter noble
        void newBoss(Noble&);
        // Changes the warrior's "boss" member variable to "nullptr"
        void getsFired();
        // Changes the warrior's "dead" status to true and "boss" member variable to "nullptr"
        void die();
        // Changes the warrior's "boss" member variable to "nullptr" and removes him from his noble's army
        bool runaway();
    private:
        std::string name;
        int strength;
        Noble* boss = nullptr;
        bool dead = false;
    };
}
#endif
