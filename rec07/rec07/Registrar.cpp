#include "Registrar.h"
#include "Student.h"
#include "Course.h"

using namespace std;

namespace BrooklynPoly {
	class Course;

	class Student;

	ostream& operator<<(ostream& os, const Registrar& rhs) {
		os << "Registrar's Report\n Courses: ";
		for (size_t i = 0; i < rhs.courses.size(); i++) {
			os << *rhs.courses[i] << endl;
		}
		os << "Students: ";
		for (size_t i = 0; i < rhs.students.size(); i++) {
			os << *rhs.students[i] << endl;
		}
		return os;
	}


	bool Registrar::addCourse(const string& name) {
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == name) {
				return false;
			}
		}
		courses.push_back(new Course(name));
		return true;
	}

	bool Registrar::addStudent(const string& name) {
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == name) {
				return false;
			}
		}
		students.push_back(new Student(name));
		return true;
	}

	size_t Registrar::findStudent(const string& name) const {
		size_t studentptr = students.size();
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == name) {
				studentptr = i;
				break;
			}
		}
		return studentptr;
	}

	size_t Registrar::findCourse(const string& name) const {
		size_t courseptr = courses.size();
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == name) {
				courseptr = i;
				break;
			}
		}
		return courseptr;
	}

	bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
		bool studentFound = false;
		bool courseFound = false;
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == courseName) { courseFound = true; break; }
		}
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == studentName) { studentFound = true; break; }
		}
		if (studentFound == false || courseFound == false) { return false; }

		Course* course = courses[findCourse(courseName)];
		Student* student = students[findStudent(studentName)];
		course->addStudent(student);
		student->addCourse(course);
		return true;
	}

	bool Registrar::cancelCourse(const string& courseName) {
		bool courseFound = false;
		size_t courseIndex = courses.size();
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == courseName) {
				courseIndex = i;
				courseFound = true;
				break;
			}
		}
		if (courseFound == false) { return false; }

		Course* course = courses[findCourse(courseName)];
		course->removeStudentsFromCourse();

		for (size_t i = courseIndex; i < courses.size() - 1; i++) {
			courses[i] = courses[i + 1];
		}
		courses.pop_back();
		return true;
	}

	void Registrar::purge() {
		for (size_t i = 0; i < courses.size(); i++) {
			delete courses[i];
		}
		courses.clear();
		for (size_t i = 0; i < students.size(); i++) {
			delete students[i];
		}
		students.clear();

	}
}
