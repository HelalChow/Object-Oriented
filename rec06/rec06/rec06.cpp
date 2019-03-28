//
//  rec06.cpp
//  rec06
//  Helal Chowdhury

//  Created by Helal Chowdhury on 3/8/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary) : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
        << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
    : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    friend ostream& operator<<(ostream& os, const Directory& d){
        os << "There are " << d.size << " entries: " << endl;
        for(size_t i = 0; i < d.size; i++){
            os << *d.entries[i] << endl;
        }
        return os;
    }
    
public:
    Directory() : size(0), capacity(1), entries(new Entry*[1]){
    }
    ~Directory(){
        for(size_t i = 0; i < size; i++){
            delete entries[i];
        }
        delete [] entries;
    }
    Directory(const Directory& other) : size(other.size), capacity(other.capacity), entries(new Entry*[other.capacity]){
  
        for(size_t i = 0; i < size; i++){
            entries[i] = new Entry(*other.entries[i]);
        }
    }
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            Entry** oldEntry = entries;
            entries = new Entry*[2*capacity];
            capacity *= 2;
            for(size_t i = 0; i < size; ++i){
                entries[i] = oldEntry[i];
            }
            delete [] oldEntry;
            
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    
    unsigned operator[](const string& name){
        for(size_t i = 0; i < size; i++){
            if (entries[i]->getName()== name){
                return entries[i]->getPhone();
            }
        }
        return -1;
    }
    
    Directory& operator=(const Directory& other){
        if(this != &other){
            for(size_t i = 0; i < size; i++){
                delete entries[i];
            }
            delete [] entries;
            size = other.size;
            capacity = other.capacity;
            size = other.size;
            capacity = other.capacity;
            entries = new Entry*[capacity];
            for(size_t i = 0; i < size; i++){
                entries[i] = new Entry(*other.entries[i]);
            }
        }
        return *this;
    }
    
private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory



void doNothing(Directory dir) { cout << dir << endl; }

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;
    
    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;
    
    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";
    
    Directory d3;
    d3 = d2;
    cout << d3 << endl;
    
//     Should display 1592
    cout << d2["Carmack"] << endl;
    
} // main


