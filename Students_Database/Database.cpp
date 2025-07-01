#include "Database.h"

// Получаем текущую дату
std::string Database::getCurrentDate()
{
	auto now = std::chrono::system_clock::now();
	return std::format("{:%d-%m-%Y}", now);
}

// Получаем список всех студентов
void Database::showAllStudents() const
{
	std::cout << "=== СПИСОК ВСЕХ СТУДЕНТОВ ===\n\n";
	for (Student student : students)
	{
		std::cout << "ID: " << student.getId()
			<< " | Имя: " << student.getName()
			<< " | Email: " << student.getEmail()
			<< " | Группа: " << student.getGroup()
			<< "\n";
	}
	std::cout << "\n";
}

// Получаем студента по ID
Student& Database::getStudentById(int id)
{
	if (id <= 0) { throw std::invalid_argument("ID не может быть отрицательным!"); }

	int index = id - 1;
	if (index >= students.size()) { throw std::out_of_range("Студент с таким ID не найден!"); }

	return students[index];
}

// Отображаем данные студента по ID
void Database::showStudentById(int id)
{
	std::cout << "\nID: " << getStudentById(id).getId()
		<< " | Имя: " << getStudentById(id).getName()
		<< " | Email: " << getStudentById(id).getEmail()
		<< " | Группа: " << getStudentById(id).getGroup()
		<< "\n\n";
}

// Получаем список всех предметов
void Database::showAllSubjects()
{
	std::cout << "=== СПИСОК ВСЕХ ПРЕДМЕТОВ ===\n\n";
	for (Subject subject : subjects)
	{
		std::cout << "ID: " << subject.getId()
			<< " | " << subject.getName()
			<< "\n";
	}
	std::cout << "\n";
}

// Получаем предмет по ID
Subject& Database::getSubjectById(int id)
{
	if (id <= 0) { throw std::invalid_argument("ID не может быть отрицательным!"); }

	int index = id - 1;
	if (index >= subjects.size()) { throw std::out_of_range("Предмет с таким ID не найден!"); }

	return subjects[index];
}

// Получаем оценки по ID студента
std::vector<StudentGrade> Database::getStudentGradesById(int studentId) const
{
	std::vector<StudentGrade> studentGrades;
	for (const StudentGrade& grade : grades)
	{
		if (grade.getStudentId() == studentId)
		{
			studentGrades.push_back(grade);
		}
	}

	if (studentGrades.empty()) { throw std::runtime_error("У студента с ID " + std::to_string(studentId) + " нет оценок"); }

	return studentGrades;
}

// Добавляем студента в список
void Database::addStudent(const Student& student)
{
	students.push_back(student);
}

// Обновляем данные существующего студента
void Database::editStudentData(Student& student)
{
	char choice;
	do
	{
		std::cout << "\nID: " << student.getId()
			<< " | Имя: " << student.getName()
			<< " | Email: " << student.getEmail()
			<< " | Группа: " << student.getGroup()
			<< "\n\n";

		std::cout << "Что нужно изменить?\n"
			<< "1. Имя\n"
			<< "2. Email\n"
			<< "3. Группа\n"
			<< "4. Назад\n";

		std::cin >> choice;

		// Переменная для изменения данных
		std::string newData;

		switch (choice)
		{
		case '1': // Обновляем имя студента
			std::cout << "Введите новое имя: ";
			std::cin >> newData;
			student.setName(newData);
			std::cout << "Имя обновлено!\n";
			break;
		case '2': // Обновляем Email студента
			std::cout << "Введите новый Email: ";
			std::cin >> newData;
			student.setEmail(newData);
			std::cout << "Email обновлён!\n";
			break;
		case '3': // Обновляем группу студента
			std::cout << "Введите новую группу: ";
			std::cin >> newData;
			student.setGroup(newData);
			std::cout << "Группа обновлена!\n";
			break;
		case '4': // "Назад"
			break;
		default:
			std::cout << "такого варианта нет!\n";
		}

	} while (choice != '4');
}

// Удаляем студента
void Database::deleteStudent(int studentId)
{
	int index = studentId - 1;
	if (index < 0 || index >= students.size()) { throw std::out_of_range("Студент с таким ID не найден!"); }

	students.erase(students.begin() + index);
	std::cout << "Студент удалён!\n\n";
}

// Добавляем новый предмет
void Database::addSubject(const Subject& subject)
{
	subjects.push_back(subject);
}

// Ставим оценку студенту
void Database::rate(int studentId, int subjectId, int grade)
{
	if (studentId <= 0 || studentId - 1 >= students.size()) { throw std::invalid_argument("Студент с таким ID не найден!"); }
	if (subjectId <= 0 || subjectId - 1 >= subjects.size()) { throw std::out_of_range("Предмет с таким ID не найден!"); }

	std::string currentDate = getCurrentDate();

	const auto& subject = getSubjectById(subjectId);
	grades.emplace_back(studentId, subjectId, subject.getName(), grade, currentDate); // Добавляем данные в список оценок

	std::cout << "\nОценка поставлена!\n\n";
	std::cout << "Нажмите Enter для продолжения...\n";
	std::cin.ignore();
	std::cin.get();
}