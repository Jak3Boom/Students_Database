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
	if (id <= 0) { throw std::invalid_argument("ID студента не может быть отрицательным!\n"); }

	auto it = std::find_if(students.begin(), students.end(),
		[id](const Student& student)
		{
			return student.getId() == id;
		});

	if (it == students.end())
	{
		throw std::out_of_range("Студент с таким ID не найден!\n");
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
void Database::showAllSubjects()
{
	std::cout << std::string(80, '=') << "\n";
	std::cout << std::format("{:^80}\n", "СПИСОК ВСЕХ ПРЕДМЕТОВ");
	std::cout << std::string(80, '=') << "\n";

	if (subjects.empty())
	{
		throw std::out_of_range("Список пуст!\n");
	}

	for (Subject subject : subjects)
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
	char choice;
	do
	{
		showStudentById(student.getId()); // Отображаем данные студента по ID

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
			std::cout << "\nИмя обновлено!\n";

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		case '2': // Обновляем Email студента
			std::cout << "Введите новый Email: ";
			std::cin >> newData;
			student.setEmail(newData);
			std::cout << "\nEmail обновлён!\n";

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		case '3': // Обновляем группу студента
			std::cout << "Введите новую группу: ";
			std::cin >> newData;
			student.setGroup(newData);
			std::cout << "\nГруппа обновлена!\n";

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		case '4': // "Назад"
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}

	} while (choice != '4');
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
	std::cout << "\nСтудент удалён!\n";
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
	std::cout << "\nОценка обновлена!\n";

	Utils::pauseScreen();
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
		throw std::out_of_range("Оценка с таким ID не найдена!");
	}

	grades.erase(it);
	std::cout << "\nОценка удалена!\n";

	Utils::pauseScreen();
}