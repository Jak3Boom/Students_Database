#include "StudentGrade.h"

int StudentGrade::gradeIdCounter = 1;

StudentGrade::StudentGrade(int studentId, int subjectId, std::string subjectName, int grade, std::string date)
	: gradeId(gradeIdCounter++),
	  studentId(studentId),
	  subjectId(subjectId),
	  subjectName(subjectName),
	  grade(grade),
	  date(date) {}

void StudentGrade::setGrade(int newData)
{
	grade = newData;
}