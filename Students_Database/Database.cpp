#include <format>
#include <algorithm>
#include <fstream>

#include "Database.h"
#include "Utils.h"

// Получаем текущую дату
std::string Database::getCurrentDate()
{
	auto now = std::chrono::system_clock::now();
	return std::format("{:%d-%m-%Y}", now);
}

// Получаем список всех студентов
void Database::showAllStudents() const
{
	std::cout << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "СПИСОК ВСЕХ СТУДЕНТОВ");
	std::cout << std::string(80, '=') << "\n";

	if (students.empty())
	{
		throw std::out_of_range("Список пуст!\n");
	}

	for (const Student& student : students)
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
	if (id <= 0) { throw std::invalid_argument("ID студента не может быть отрицательным!\n"); }

	auto it = std::find_if(students.begin(), students.end(),
		[id](const Student& student)
		{
			return student.getId() == id;
		});

	if (it == students.end())
	{
		throw std::out_of_range(std::format("Студент с ID {} не найден!\n", id));
	}

	return *it;
}

// Отображаем данные студента по ID
void Database::showStudentById(int id)
{
	const Student& student = getStudentById(id);

	std::cout << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "ДАННЫЕ СТУДЕНТА");
	std::cout << std::string(80, '=');

	std::cout << std::format("\nID: {} | Имя: {} | Email: {} | Группа: {}\n",
		student.getId(),
		student.getName(),
		student.getEmail(),
		student.getGroup());

	std::cout << std::string(80, '=') << "\n";
}

// Получаем список всех предметов
void Database::showAllSubjects() const
{
	std::cout << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "СПИСОК ВСЕХ ПРЕДМЕТОВ");
	std::cout << std::string(80, '=') << "\n";

	if (subjects.empty())
	{
		throw std::out_of_range("Список пуст!\n");
	}

	for (const Subject& subject : subjects)
	{
		std::cout << std::format("ID: {} | {}\n",
			subject.getId(),
			subject.getName());
	}
	std::cout << std::string(80, '=') << "\n";
}

// Получаем предмет по ID
Subject& Database::getSubjectById(int id)
{
	if (id <= 0) { throw std::invalid_argument("ID предмета не может быть отрицательным!\n"); }

	auto it = std::find_if(subjects.begin(), subjects.end(),
		[id](const Subject& subject)
		{
			return subject.getId() == id;
		});

	if (it == subjects.end())
	{
		throw std::out_of_range("Предмет с таким ID не найден!\n");
	}

	return *it;
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
	if (id <= 0) { throw std::invalid_argument("ID оценки не может быть отрицательным!\n"); }

	auto it = std::find_if(grades.begin(), grades.end(),
		[id](const StudentGrade& grade)
		{
			return grade.getGradeId() == id;
		});

	if (it == grades.end())
	{
		throw std::out_of_range(std::format("Оценка с ID {} не найдена!\n", id));
	}

	return *it;
}

// Отображаем все оценки студента
void Database::showAllStudentGrades(int studentId)
{
	if (studentId <= 0) { throw std::invalid_argument("ID студента не может быть отрицательным!\n"); }
	const Student& student = getStudentById(studentId);

	auto grades = getStudentGradesById(studentId);

	if (grades.empty())	{ throw std::out_of_range(std::format("У студента с ID {} пока нет оценок.\n", studentId)); }

	std::cout << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "ОЦЕНКИ СТУДЕНТА");
	std::cout << std::string(80, '=') << "\n";

	for (const StudentGrade& data : grades) {
		std::cout << std::format("ID: {} | {} | Оценка: {} | {}\n",
			data.getGradeId(),
			data.getSubjectName(),
			data.getGrade(),
			data.getDate());
	}
	std::cout << std::string(80, '=') << "\n";
}

// Добавляем студента в список
void Database::addStudent(const std::string& name, const std::string& email, const std::string& group)
{
	students.emplace_back(name, email, group);
}

// Обновляем данные существующего студента
void Database::editStudentData(Student& student)
{
	int choice = 0;
	do
	{
		do
		{
			Utils::clearScreen();
			showStudentById(student.getId()); // Отображаем данные студента по ID
			std::cout << "Что нужно изменить?\n"
				<< "1. Имя\n"
				<< "2. Email\n"
				<< "3. Группа\n"
				<< "4. Назад\n";

			std::cin >> choice;
		} while (choice <= 0 || choice > 4);

		// Переменная для изменения данных
		std::string newData;

		switch (choice)
		{
		case 1: // Обновляем имя студента
		{
			std::cout << "Введите новое имя: ";
			std::cin >> newData;
			student.setName(newData);
			std::cout << "\nИмя обновлено!\n";

			Utils::pauseScreen();
			break;
		}
		case 2: // Обновляем Email студента
		{
			std::cout << "Введите новый Email: ";
			std::cin >> newData;
			student.setEmail(newData);
			std::cout << "\nEmail обновлён!\n";

			Utils::pauseScreen();
			break;
		}
		case 3: // Обновляем группу студента
		{
			std::cout << "Введите новую группу: ";
			std::cin >> newData;
			student.setGroup(newData);
			std::cout << "\nГруппа обновлена!\n";

			Utils::pauseScreen();
			break;
		}
		case 4: // "Назад"
			Utils::clearScreen();
			break;
		default:
			std::cout << "Такого варианта нет!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
		}

	} while (choice != 4);
}

// Удаляем студента
void Database::deleteStudent(int studentId)
{
	if (studentId <= 0) { throw std::invalid_argument("ID студента не может быть отрицательным!\n"); }

	auto it = std::find_if(students.begin(), students.end(),
		[studentId](const Student& student)
		{
			return student.getId() == studentId;
		});

	if (it == students.end())
	{
		throw std::out_of_range("Студент с таким ID не найден!\n");
	}

	students.erase(it);
}

// Добавляем новый предмет
void Database::addSubject(int id, const std::string& name)
{
	if (id <= 0) { throw std::invalid_argument("ID предмета не может быть отрицательным!\n"); }

	for (const Subject& subject : subjects)
	{
		if (id == subject.getId())
		{
			throw std::invalid_argument(std::format("Предмет с ID {} уже существует!\n", id));
		}
	}

	subjects.emplace_back(id, name);
}

// Ставим оценку студенту
void Database::rate(int studentId, int subjectId, int grade)
{
	const auto& student = getStudentById(studentId);
	const auto& subject = getSubjectById(subjectId);

	std::string currentDate = getCurrentDate();
	grades.emplace_back(studentId, subjectId, subject.getName(), grade, currentDate); // Добавляем данные в список оценок
}

// Обновляем данные об оценке
void Database::editGradeData(StudentGrade& grade)
{
	int newData;
	do
	{
		std::cout << "Введите новую оценку от 0 до 5: ";
		std::cin >> newData;
	} while (newData < 0 || newData > 5); // Проверка, входит ли введённое значение в необходимый диапазон

	grade.setGrade(newData);
}

// Удаляем оценку по ID
void Database::deleteGrade(int gradeId)
{
	if (gradeId <= 0) { throw std::invalid_argument("ID оценки не может быть отрицательным!\n"); }

	auto it = std::find_if(grades.begin(), grades.end(),
		[gradeId](const StudentGrade& studentGrade)
		{
			return studentGrade.getGradeId() == gradeId;
		});

	if (it == grades.end())
	{
		throw std::out_of_range(std::format("Оценка с ID {} не найдена!\n", gradeId));
	}

	grades.erase(it);
}

// Загрузка данных из файлов
void Database::loadFromFiles()
{
	students.clear();
	subjects.clear();
	grades.clear();

	// Загрузка студентов из students.txt
	std::ifstream studentsFile("students.txt");
	if (studentsFile.is_open())
	{
		std::string line;
		std::getline(studentsFile, line); // Пропускаем шапку
		while (std::getline(studentsFile, line))
		{
			size_t pos = 0;
			size_t nextPos;

			// Извлечение id
			nextPos = line.find("|", pos);
			std::string id = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение name
			nextPos = line.find("|", pos);
			std::string name = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение email
			nextPos = line.find("|", pos);
			std::string email = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение group
			std::string group = line.substr(pos);

			addStudent(name, email, group);
		}
	}
	studentsFile.close();

	// Загрузка предметов из subjects.txt
	std::ifstream subjectsFile("subjects.txt");
	if (subjectsFile.is_open())
	{
		std::string line;
		std::getline(subjectsFile, line); // Пропускаем шапку
		while (std::getline(subjectsFile, line))
		{
			size_t pos = 0;
			size_t nextPos;

			// Извлечение id
			nextPos = line.find("|", pos);
			std::string id = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение name
			std::string name = line.substr(pos);

			addSubject(std::stoi(id), name);
		}
	}
	subjectsFile.close();

	// Загрузка оценок из grades.txt
	std::ifstream gradesFile("grades.txt");
	if (gradesFile.is_open())
	{
		std::string line;
		std::getline(gradesFile, line); // Пропускаем шапку
		while (std::getline(gradesFile, line))
		{
			size_t pos = 0;
			size_t nextPos;

			// Извлечение gradeId
			nextPos = line.find("|", pos);
			std::string gradeId = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение studentId
			nextPos = line.find("|", pos);
			std::string studentId = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение subjectId
			nextPos = line.find("|", pos);
			std::string subjectId = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение subjectName
			nextPos = line.find("|", pos);
			std::string subjectName = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение grade
			nextPos = line.find("|", pos);
			std::string grade = line.substr(pos, nextPos - pos);
			pos = nextPos + 1;

			// Извлечение date
			std::string date = line.substr(pos);

			grades.emplace_back(std::stoi(studentId), std::stoi(subjectId), subjectName, std::stoi(grade), date);
		}
	}
	gradesFile.close();
}

// Сохранение данных в файл
void Database::saveToFiles() const
{
	// Сохранение данных студентов в файл
	std::ofstream studentsFile("students.txt");
	if (!studentsFile.is_open()) {
		std::cerr << "Ошибка открытия файла students.txt\n";
		return;
	}
	studentsFile << "id | name | email | group\n";
	for (const auto& student : students) {
		studentsFile << student.getId() << "|"
			<< student.getName() << "|"
			<< student.getEmail() << "|"
			<< student.getGroup() << "\n";
	}
	studentsFile.close();

	// Сохранение данных о предметах в файл
	std::ofstream subjectsFile("subjects.txt");
	if (!subjectsFile.is_open())
	{
		std::cerr << "Ошибка открытия файла subjects.txt\n";
		return;
	}
	subjectsFile << "id | name\n";
	for (const auto& subject : subjects)
	{
		subjectsFile << subject.getId() << "|"
			<< subject.getName() << "\n";
	}
	subjectsFile.close();

	// Сохранение данных об оценках в файл
	std::ofstream gradesFile("grades.txt");
	if (!gradesFile.is_open())
	{
		std::cerr << "Ошибка открытия файла grades.txt\n";
		return;
	}
	gradesFile << "grade_id | student_id | subject_id | subject_name | grade | date\n";
	for (const auto& grade : grades)
	{
		gradesFile << grade.getGradeId() << "|"
			<< grade.getStudentId() << "|"
			<< grade.getSubjectId() << "|"
			<< grade.getSubjectName() << "|"
			<< grade.getGrade() << "|"
			<< grade.getDate() << "\n";
	}
	gradesFile.close();
}