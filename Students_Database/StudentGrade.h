#pragma once
#include <string>

class StudentGrade
{
private:
	int studentId;
	int subjectId;
	std::string subjectName;
	int grade;
	std::string date;

public:
	StudentGrade(int studentId, int subjectId, std::string subjectName, int grade, std::string date);

	int getStudentId() const { return studentId; }
	int getSubjectId() const { return subjectId; }
	std::string getSubjectName() const { return subjectName; }
	int getGrade() const { return grade; }
	std::string getDate() const { return date; }
};