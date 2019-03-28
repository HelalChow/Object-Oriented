#include "Student.h"
#include "Course.h"
using namespace std;

namespace BrooklynPoly {
	class Course;

	ostream& operator<<(ostream& os, const Student& rhs) {
		os << rhs.getName() << ": ";
		if (rhs.courses.size() == 0) { os << "No Courses"; }
		else {
			for (size_t i = 0; i < rhs.courses.size(); i++) {
				os << rhs.courses[i]->getName() << " ";
			}
			os << endl;
		}
		return os;
	}


	Student::Student(const string& name) : name(name) {}
	const string& Student::getName() const { return name; }

	bool Student::addCourse(Course* c) {
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i] == c) {
				return false;
			}
		}
		courses.push_back(c);
		return true;
	}
	void Student::removedFromCourse(Course* c) {
		size_t courseIndex = 0;
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i] == c) {
				courseIndex = i;
				break;
			}
		}
		for (size_t i = courseIndex; i < courses.size() - 1; i++) {
			courses[i] = courses[i + 1];
		}
		courses.pop_back();
	}
}
