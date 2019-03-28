#ifndef BROOKLYN_POLY_COURSE
#define BROOKLYN_POLY_COURSE

#include <iostream>
#include <string.h>
#include <vector>

namespace BrooklynPoly {
	class Student;
	
	class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
	public:
		// Course methods needed by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
		bool addStudent(Student* p);
		void removeStudentsFromCourse();


	private:
        std::string name;
        std::vector<Student*> students;
	};
}
#endif
