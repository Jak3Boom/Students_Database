#include "Database.h"

// Получаем список всех студентов
void Database::GetAllStudents()
{
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
Student& Database::GetStudentById(int id)
{
	if (id <= 0)
	{
		throw std::invalid_argument("ID не может быть отрицательным!");
	}

	int index = id - 1;
	if (index >= students.size())
	{
		throw std::out_of_range("Студент с таким ID не найден!");
	}

	return students[index];
}

// Добавляем студента в список
void Database::AddStudent(const Student& student)
{
	students.push_back(student);
}

// Обновляем данные существующего студента
void Database::EditStudentData(Student& student)
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
void Database::DeleteStudent(int studentId)
{
	int index = studentId - 1;
	if (index < 0 || index >= students.size())
	{
		throw std::out_of_range("Студент с таким ID не найден!");
	}
	students.erase(students.begin() + index);
	std::cout << "Студент удалён!\n\n";
}