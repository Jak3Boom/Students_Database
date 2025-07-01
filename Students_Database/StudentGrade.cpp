#include "StudentGrade.h"

StudentGrade::StudentGrade(int studentId, int subjectId, std::string subjectName, int grade, std::string date)
	: studentId(studentId),
	  subjectId(subjectId),
	  subjectName(subjectName),
	  grade(grade),
	  date(date) {}
