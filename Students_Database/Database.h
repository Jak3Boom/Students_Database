#pragma once
#include <iostream>
#include <vector>
#include <chrono>

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
	std::string getCurrentDate();

// Получение данных из базы
	// Студенты
	void showAllStudents() const;
	Student& getStudentById(int id);
	void showStudentById(int id);

	// Предметы
	void showAllSubjects();
	Subject& getSubjectById(int id);

	// Оценки
	std::vector<StudentGrade> getStudentGradesById(int studentId);
	StudentGrade& getGradeById(int id);
	void showAllStudentGrades(int studentId);

// Обновление данных

	// Студенты
	void addStudent(const Student& student);
	void editStudentData(Student& student);
	void deleteStudent(int studentId);

	// Предметы
	void addSubject(const Subject& subject);

	// Оценки
	void rate(int studentId, int subjectId, int grade);
	void editGradeData(StudentGrade& grade);
	void deleteGradeById(int gradeId);
};