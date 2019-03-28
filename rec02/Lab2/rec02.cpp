//
//  rec02.cpp
//  Lab2
//  Helal Chowdhury
//  Created by Helal Chowdhury on 2/8/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct molecule {
    vector<string> names;
    int carbonNumber;
    int hydrogenNumber;
};

void openStream(ifstream& text);
void locateFormula(const string& name, int cNum, int hNum, vector<molecule>& allMolecules, bool& oldFound);
void assignMolecule(const string& name, int cNum, int hNum, vector<molecule>& allMolecules);
void fillVector(ifstream& text, vector<molecule>& allMolecules);
void sortMolecules(vector<molecule>& allMolecules);
void displayMolecules(const vector<molecule>& allMolecules);



int main() {
    ifstream text;
    vector<molecule> allMolecules;
    
    openStream(text);
    fillVector(text, allMolecules);
    sortMolecules(allMolecules);
    displayMolecules(allMolecules);
}

// Asks for a name of file and attemps to open. Re-asks if there was error
void openStream(ifstream& text) {
    string fileName;
    bool fileOpen = false;
    
    while (fileOpen == false) {
        cout << "What text file would you want to open?" << endl;
        cin >> fileName;
        text.open(fileName);
        if(!text) {
            cerr << "Failed to open " << fileName << ". Please try again.";
            text.clear();
        }
        else{
            fileOpen = true;
        }
    }
    
}

// Checks if there is a molecule with the same formula
void locateFormula(const string& name, int cNum, int hNum, vector<molecule>& allMolecules, bool& oldFound) {
    for(size_t i = 0; i < allMolecules.size(); i++) {
        if(allMolecules[i].carbonNumber == cNum && allMolecules[i].hydrogenNumber == hNum){
            allMolecules[i].names.push_back(name);
            oldFound = true;
        }
    }
}

// Creates new molecule and inserts into the vector of molecules
void assignMolecule(const string& name, int cNum, int hNum, vector<molecule>& allMolecules){
    bool oldFound = false;
    locateFormula(name, cNum, hNum, allMolecules, oldFound);
    if (oldFound == false) {
        molecule moleculeNew;
        moleculeNew.names = {name};
        moleculeNew.carbonNumber = cNum;
        moleculeNew.hydrogenNumber = hNum;
        allMolecules.push_back(moleculeNew);
    }
}

// Fills the vector with molecules
void fillVector(ifstream& text, vector<molecule>& allMolecules) {
    string name;
    char c;
    int cNum, hNum;
    
    while (text >> name >> c >> cNum >> c >> hNum) {
        assignMolecule(name, cNum, hNum, allMolecules);
    }
}


// Sorts all the molecules based on Carbon then Hydrogen numbers
void sortMolecules(vector<molecule>& allMolecules) {
    bool swapped;
    
    for (int i = 0; i < allMolecules.size() - 1; i++) {
        swapped = false;
        for (int j = 0; j < allMolecules.size() - i - 1; j++) {
            if (allMolecules[j].carbonNumber > allMolecules[j+1].carbonNumber){
                swap(allMolecules[j], allMolecules[j+1]);
                swapped = true;
            }
            else if (allMolecules[j].carbonNumber == allMolecules[j+1].carbonNumber){
                if (allMolecules[j].hydrogenNumber > allMolecules[j+1].hydrogenNumber) {
                    swap(allMolecules[j], allMolecules[j+1]);
                    swapped = true;
                }
            }
        }
    }
}

// Displays all molecules in vector with the formula, and all the names with that formula
void displayMolecules(const vector<molecule>& allMolecules) {
    for (int i = 0; i < allMolecules.size(); i++) {
        cout << "C" << allMolecules[i].carbonNumber << "H" << allMolecules[i].hydrogenNumber
        << " ";
        for (int j = 0; j < allMolecules[i].names.size(); j++) {
            cout << allMolecules[i].names[j] << " ";
        }
        cout << endl;
    }
}
