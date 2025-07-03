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
	std::cout << "\n" << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "СПИСОК ВСЕХ СТУДЕНТОВ");
	std::cout << std::string(80, '=') << "\n";
	for (Student student : students)
	{
		std::cout << std::format("ID: {} | Имя: {} | Email: {} | Группа: {}\n",
			student.getId(),
			student.getName(),
			student.getEmail(),
			student.getGroup());
	}
	std::cout << std::string(80, '=') << "\n";
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
	std::cout << std::format("\nID: {} | Имя: {} | Email: {} | Группа: {}\n",
		getStudentById(id).getId(),
		getStudentById(id).getName(),
		getStudentById(id).getEmail(),
		getStudentById(id).getGroup());
}

// Получаем список всех предметов
void Database::showAllSubjects()
{
	std::cout << "\n" << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "СПИСОК ВСЕХ ПРЕДМЕТОВ");
	std::cout << std::string(80, '=') << "\n";
	for (Subject subject : subjects)
	{
		std::cout << std::format("ID: {} | {}\n", subject.getId(), subject.getName());
	}
	std::cout << std::string(80, '=') << "\n";
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
std::vector<StudentGrade> Database::getStudentGradesById(int studentId)
{
	std::vector<StudentGrade> studentGrades;
	for (const StudentGrade& grade : grades)
	{
		if (grade.getStudentId() == studentId)
		{
			studentGrades.push_back(grade);
		}
	}
	return studentGrades;
}

// Получаем оценку по ID
StudentGrade& Database::getGradeById(int id)
{
	if (id <= 0) { throw std::invalid_argument("ID не может быть отрицательным!\n"); }

	int index = id - 1;
	if (index >= grades.size()) { throw std::out_of_range("Оценка с таким ID не найдена!\n"); }

	return grades[index];
}

// Отображаем все оценки студента
void Database::showAllStudentGrades(int studentId)
{
	auto grades = getStudentGradesById(studentId);

	if (grades.empty())
	{
		std::cout << std::format("\nУ студента с ID {} пока нет оценок.\n\n", studentId);
		return;
	}

	std::cout << "\n" << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "ОЦЕНКИ СТУДЕНТА");
	std::cout << std::string(80, '=') << "\n";

	for (const StudentGrade& data : grades) {
		std::cout << std::format("ID: {} | {} | Оценка: {} | {}\n",
			data.getGradeId(),
			data.getSubjectName(),
			data.getGrade(),
			data.getDate());
	}
	std::cout << std::string(80, '=') << "\n\n";
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
	if (studentId <= 0 || studentId - 1 >= students.size())
	{
		std::cout << std::format("\nСтудент с ID {} не найден.\n\n", studentId);
		return;
	}
	if (subjectId <= 0 || subjectId - 1 >= subjects.size())
	{
		std::cout << std::format("\nПредмет с ID {} не найден.\n\n", subjectId);
		return;
	}

	std::string currentDate = getCurrentDate();

	const auto& subject = getSubjectById(subjectId);
	grades.emplace_back(studentId, subjectId, subject.getName(), grade, currentDate); // Добавляем данные в список оценок

	std::cout << "\nОценка поставлена!\n\n";
	std::cout << "Нажмите Enter для продолжения...\n";
	std::cin.ignore();
	std::cin.get();
}

void Database::editGradeData(StudentGrade& grade)
{
	int newData;
	do
	{
		std::cout << "Введите новую оценку от 0 до 5: ";
		std::cin >> newData;
	} while (newData < 0 || newData > 5); // Проверка, входит ли введённое значение в необходимый диапазон

	grade.setGrade(newData);
	std::cout << "Оценка обновлена!\n";
}

// Удаляем оценку по ID
void Database::deleteGradeById(int gradeId)
{
	int index = gradeId - 1;
	if (index < 0 || index >= grades.size()) { throw std::out_of_range("Оценка с таким ID не найдена!"); }

	grades.erase(grades.begin() + index);
	std::cout << "Оценка удалена!\n";
}