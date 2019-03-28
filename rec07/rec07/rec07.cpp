///*
// rec07
// Starter Code for required functionality
// Yes, you may add other methods.
// */
//
//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//class Student;
//
//class Course {
//    friend ostream& operator<<(ostream& os, const Course& rhs);
//public:
//    // Course methods needed by Registrar
//    Course(const string& courseName);
//    const string& getName() const;
//    bool addStudent(Student*);
//    void removeStudentsFromCourse();
//
//
//private:
//    string name;
//    vector<Student*> students;
//};
//
//class Student {
//    friend ostream& operator<<(ostream& os, const Student& rhs);
//public:
//    // Student methods needed by Registrar
//    Student(const string& name);
//    const string& getName() const;
//    bool addCourse(Course*);
//
//    // Student method needed by Course
//    void removedFromCourse(Course*);
//
//private:
//    string name;
//    vector<Course*> courses;
//};
//
//class Registrar {
//    friend ostream& operator<<(ostream& os, const Registrar& rhs);
//public:
////    Registrar();
//    bool addCourse(const string&);
//    bool addStudent(const string&);
//    bool enrollStudentInCourse(const string& studentName,
//                               const string& courseName);
//    bool cancelCourse(const string& courseName);
//    void purge();
//
//
//private:
//    size_t findStudent(const string&) const;
//    size_t findCourse(const string&) const;
//
//    vector<Course*> courses;
//    vector<Student*> students;
//};
//
//int main() {
//
//    Registrar registrar;
//
//    cout << "No courses or students added yet\n";
//    cout << registrar << endl;
//
//    cout << "AddCourse CS101.001\n";
//    registrar.addCourse("CS101.001");
//    cout << registrar << endl;
//
//    cout << "AddStudent FritzTheCat\n";
//    registrar.addStudent("FritzTheCat");
//    cout << registrar << endl;
//
//    cout << "AddCourse CS102.001\n";
//    registrar.addCourse("CS102.001");
//    cout << registrar << endl;
//
//    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
//    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
//    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
//    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
//    cout << registrar << endl;
//
//    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
//    cout << "Should fail, i.e. do nothing, "
//    << "since Bullwinkle is not a student.\n";
//    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
//    cout << registrar << endl;
//
//    cout << "CancelCourse CS102.001\n";
//    registrar.cancelCourse("CS102.001");
//    cout << registrar << endl;
//
//    /*
//     // [OPTIONAL - do later if time]
//     cout << "ChangeStudentName FritzTheCat MightyMouse\n";
//     registrar.changeStudentName("FritzTheCat", "MightyMouse");
//     cout << registrar << endl;
//
//     cout << "DropStudentFromCourse MightyMouse CS101.001\n";
//     registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
//     cout << registrar << endl;
//
//     cout << "RemoveStudent FritzTheCat\n";
//     registrar.removeStudent("FritzTheCat");
//     cout << registrar << endl;
//     */
//
//    cout << "Purge for start of next semester\n";
//    registrar.purge();
//    cout << registrar << endl;
//}
//
////  Course Methods
//ostream& operator<<(ostream& os, const Course& rhs){
//    os << rhs.getName() << ": ";
//    if(rhs.students.size() == 0){os << "No Students";}
//    else{
//        for(size_t i = 0; i < rhs.students.size(); i++){
//            os << rhs.students[i]->getName() << " ";
//        }
//        os << endl;
//    }
//    return os;
//}
//
////
////
////Course :: Course(const string& courseName) : name(courseName){}
////const string& Course:: getName() const {return name;}
////bool Course::addStudent(Student* p){
////    for(size_t i =0; i < students.size(); i++){
////        if(students[i] == p){
////            return false;
////        }
////    }
////    students.push_back(p);
////    return true;
////}
////void Course :: removeStudentsFromCourse(){
////    for(size_t i =0; i < students.size(); i++){
////        students[i]->removedFromCourse(this);
////    }
////    students.clear();
////}
////
////
//////  Student Methods
////ostream& operator<<(ostream& os, const Student& rhs){
////    os << rhs.getName() << ": ";
////    if(rhs.courses.size() == 0){os << "No Courses";}
////    else{
////        for(size_t i = 0; i < rhs.courses.size(); i++){
////            os << rhs.courses[i]->getName() << " ";
////        }
////        os << endl;
////    }
////    return os;
////}
////
////
////Student::Student(const string& name) : name(name) {}
////const string& Student:: getName() const{return name;}
////
////bool Student::addCourse(Course* c){
////    for(size_t i =0; i < courses.size(); i++){
////        if(courses[i] == c){
////            return false;
////        }
////    }
////    courses.push_back(c);
////    return true;
////}
////void Student::removedFromCourse(Course* c){
////    size_t courseIndex = 0;
////    for(size_t i =0; i < courses.size(); i++){
////        if(courses[i]==c){
////            courseIndex = i;
//            break;
//        }
//    }
//    for(size_t i = courseIndex;i < courses.size()-1; i++){
//        courses[i] = courses[i+1];
//    }
//    courses.pop_back();
//}
//
//
//
////  Registrar Methods
//ostream& operator<<(ostream& os, const Registrar& rhs){
//    os << "Registrar's Report\n Courses: ";
//    for(size_t i = 0; i < rhs.courses.size(); i++){
//        os << *rhs.courses[i] << endl;
//    }
//    os << "Students: ";
//    for(size_t i = 0; i < rhs.students.size(); i++){
//        os << *rhs.students[i] << endl;
//    }
//    return os;
//}
//
//
//bool Registrar::addCourse(const string& name){
//    for(size_t i =0; i < courses.size(); i++){
//        if(courses[i]->getName() == name){
//            return false;
//        }
//    }
//    courses.push_back(new Course(name));
//    return true;
//}
//
//bool Registrar::addStudent(const string& name){
//    for(size_t i = 0; i < students.size(); i++){
//        if(students[i]->getName() == name){
//            return false;
//        }
//    }
//    students.push_back(new Student(name));
//    return true;
//}
//
//size_t Registrar::findStudent(const string& name) const{
//    size_t studentptr = students.size();
//    for(size_t i = 0; i < students.size(); i++){
//        if (students[i]->getName() == name){
//            studentptr = i;
//            break;
//        }
//    }
//    return studentptr;
//}
//
//size_t Registrar::findCourse(const string& name) const{
//    size_t courseptr = courses.size();
//    for(size_t i = 0; i < courses.size(); i++){
//        if (courses[i]->getName() == name){
//            courseptr = i;
//            break;
//        }
//    }
//    return courseptr;
//}
//
//bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
//    bool studentFound = false;
//    bool courseFound = false;
//    for(size_t i =0; i< courses.size(); i++){
//        if(courses[i]->getName() == courseName){courseFound = true; break;}
//    }
//    for(size_t i =0; i< students.size(); i++){
//        if(students[i]->getName() == studentName){studentFound = true; break;}
//    }
//    if(studentFound == false || courseFound == false){return false;}
//    
//    Course* course = courses[findCourse(courseName)];
//    Student* student  = students[findStudent(studentName)];
//    course->addStudent(student);
//    student->addCourse(course);
//    return true;
//}
//
//bool Registrar::cancelCourse(const string& courseName){
//    bool courseFound = false;
//    size_t courseIndex = courses.size();
//    for(size_t i =0; i< courses.size(); i++){
//        if(courses[i]->getName() == courseName){
//            courseIndex = i;
//            courseFound = true;
//            break;
//        }
//    }
//    if(courseFound == false){return false;}
//    
//    Course* course = courses[findCourse(courseName)];
//    course->removeStudentsFromCourse();
//    
//    for(size_t i = courseIndex; i < courses.size()-1; i++){
//        courses[i] = courses[i+1];
//    }
//    courses.pop_back();
//    return true;
//}
//
//void Registrar :: purge(){
//    for(size_t i = 0; i < courses.size(); i++){
//        delete courses[i];
//    }
//    courses.clear();
//    for(size_t i = 0; i < students.size(); i++){
//        delete students[i];
//    }
//    students.clear();
//    
//}
