#pragma once
#include <iostream>
#include <vector>

#include "Student.h"
#include "Subject.h"
#include "StudentGrade.h"

class Database
{
private:
	std::vector<Student> students;
	std::vector<Subject> subjects;
	std::vector<StudentGrade> grades;
public:
	// Получение данных из базы
	void GetAllStudents();
	Student& GetStudentById(int id);

	// Обновление данных
	void AddStudent(const Student& student);
	void EditStudentData(Student& student);
	void DeleteStudent(int studentId);
};