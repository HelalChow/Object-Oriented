//
//  rec05.cpp
//  rec05
//  Helal Chowdhury

//  Created by Helal Chowdhury on 3/1/19.
//  Copyright © 2019 Helal Chowdhury. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;




class Section{
    friend ostream& operator<<(ostream& os, const Section& section)
    {
        os << "Section: " << section.name << ", Time slot: " << section.time << ", Students: ";
        if (section.record.size() == 0){os << "None"; return os;}
        os << endl;
        for(StudentRecord* report: section.record){
            os << *report << endl;
        }
        
        return os;
    }
    
public:
    Section(const string& Sectname, const string& day, int time) : name(Sectname), time(day, time){}
    Section(const Section& section) : time(section.time), name(section.name) {
        for (const StudentRecord* studentRecord : section.record) {
            record.push_back(new StudentRecord(*studentRecord));
        }
    }
    ~Section(){
        cout << "Section " << name << " is being deleted" << endl;
        for(StudentRecord* reports: record){
            cout << "Deleting " << reports->getName() << endl;
            delete reports;
            
        }
        
    }
    
    void addStudent(const string& name){
        record.push_back( new StudentRecord(name));
    }
    
    void setGrade(const string& name, int index, int grade){
        for(size_t i = 0; i < record.size(); i++){
            if (record[i]->getName() == name){
                record[i]->changeReport(index, grade);
                break;
            }
        }
    }
    
    
private:
    class StudentRecord{
        friend ostream& operator<<(ostream& os, const StudentRecord record){
            os << "Name: " << record.name << ", Grades: ";
            for(int grade: record.report){
                os << grade << " ";
            }
            return os;
        }
    public:
        StudentRecord(const string& name):name(name){}
        string getName() const {return name;}
        void changeReport(int index, int grade){
            report[index-1] = grade;
        }
        
        
        
    private:
        string name;
        vector<int> report = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        
    };
    
    class TimeSlot{
        friend ostream& operator<<(ostream& os, const TimeSlot time){
            os << "[Day: " << time.day << ", Start time: ";
            if (time.hour > 12){
                os << (time.hour - 12) << "pm]";
            }
            else{
                os << (time.hour) << "am ]";
            }
            
            return os;
        }
    public:
        TimeSlot(const string& day, int time): day(day), hour(time) {}
        
    private:
        string day;
        int hour;
    };
    string name;
    vector<StudentRecord*> record;
    TimeSlot time;
    
    
    
};


class LabWorker{
    friend ostream& operator<<(ostream& os, const LabWorker& person){
        if(person.section == 0){os << person.name << " does not have a section" << endl;}
        else{
            os << person.name << " has " << *person.section;
        }
        return os;
    }
public:
    LabWorker(const string& name): name(name){}
    
    void addSection(Section& sect) {
        section = &sect;
    }
    
    void addGrade(string name, int grade, int index){
        section->setGrade(name, index, grade);
    }
    
    
    
private:
    string name;
    Section* section;
};








// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {
    
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;
    
    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;
    
    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;
    
    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;
    
    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;
    
    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;
    
    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;
    
    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
    << "those students (or rather their records?)\n";
    
    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
    << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    
} // main

