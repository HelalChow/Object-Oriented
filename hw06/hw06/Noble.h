//
//  Noble.hpp
//  hw06
//
//  Created by Helal Chowdhury on 3/25/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

#ifndef NOBLE_H
#define NOBLE_H
namespace WarriorCraft {
    class Warrior;
    
    class Noble {
        friend std::ostream& operator<<(std::ostream&, const Noble&);
    public:
        Noble(const std::string&);
        // Returns the noble's army
        int getTotalStrength() const;
        // Returns the noble's name
        std::string getName() const;
        bool isDead() const;
        // Takes in a warrior and places him into the noble's army
        bool hire(Warrior&);
        // Takes in and removes a warrior from the noble's army
        bool fire(Warrior&);
        // Takes in a noble and simulates a battle
        void battle(Noble&);
        // Removes Warrior from the vector of Warrior pointers
        void remove(Warrior&);
    private:
        std::string name;
        std::vector<Warrior*> army;
        double totalStrength = 0;
        bool dead = false;
    };
}
#endif
