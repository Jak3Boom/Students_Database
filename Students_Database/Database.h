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
	void showAllSubjects() const;
	Subject& getSubjectById(int id);

	// Оценки
	std::vector<StudentGrade> getStudentGradesById(int studentId);
	StudentGrade& getGradeById(int id);
	void showAllStudentGrades(int studentId);

// Обновление данных
	// Студенты
	void addStudent(const std::string& name, const std::string& email, const std::string& group);
	void editStudentData(Student& student);
	void deleteStudent(int studentId);

	// Предметы
	void addSubject(int id, const std::string& name);

	// Оценки
	void rate(int studentId, int subjectId, int grade);
	void editGradeData(StudentGrade& grade);
	void deleteGrade(int gradeId);

// Работа с файлами
	void loadFromFiles();
	void saveToFiles() const;
};