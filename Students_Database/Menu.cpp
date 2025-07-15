#include "Menu.h"
#include "Utils.h"

/*==================== ГЛАВНОЕ МЕНЮ ====================*/
void mainMenu(Database& db)
{
	std::string input;
	char choice;

	do
	{
		std::cout << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "ГЛАВНОЕ МЕНЮ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Управление студентами\n";
		std::cout << "2. Управление предметами\n";
		std::cout << "3. Управление оценками\n";
		std::cout << "4. Выход\n";

		std::cin >> input;

		// Проверка ввода
		if (input.length() == 1 && input[0] >= '1' && input[0] <= '4')
		{
			choice = input[0];
		}
		else
		{
			choice = '0';
			std::cout << "\nВведите цифру от 1 до 4!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			continue;
		}

		switch (choice)
		{
		case '1': // Меню управления студентами
			Utils::clearScreen();
			studentMenu(db);
			break;
		case '2': // Меню управления предметами
			Utils::clearScreen();
			subjectMenu(db);
			break;
		case '3': // Меню управления оценками
			Utils::clearScreen();
			gradesMenu(db);
			break;
		case '4': // Выход
			std::cout << "До свидания!\n";
			break;
		default:
			Utils::clearScreen();
		}

	} while (choice != '4');
}

/*==================== МЕНЮ УПРАВЛЕНИЯ СТУДЕНТАМИ ====================*/
void studentMenu(Database& db)
{
	std::string input;
	char choice;

	do
	{
		std::cout << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "МЕНЮ УПРАВЛЕНИЯ СТУДЕНТАМИ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Добавить нового студента\n";
		std::cout << "2. Получить список всех студентов\n";
		std::cout << "3. Получить студента по ID\n";
		std::cout << "4. Изменить данные студента\n";
		std::cout << "5. Удалить студента из списка\n";
		std::cout << "6. Назад\n";

		std::cin >> input;

		// Проверка ввода
		if (input.length() == 1 && input[0] >= '1' && input[0] <= '6')
		{
			choice = input[0];
		}
		else
		{
			choice = '0';
			std::cout << "\nВведите цифру от 1 до 6!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			continue;
		}

		switch (choice)
		{
		case '1': // Добавляем нового студента
		{
			Utils::clearScreen();

			std::string name, email, group;

			std::cout << "Введите имя студента: ";
			std::cin >> name;

			std::cout << "Введите email студента: ";
			std::cin >> email;

			std::cout << "Введите группу студента: ";
			std::cin >> group;

			// Добавляем студента в базу данных
			db.addStudent(name, email, group);

			std::cout << "\nСтудент добавлен!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '2': // Получаем список всех студентов
		{
			Utils::clearScreen();

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '3': // Получаем студента по ID
		{
			Utils::clearScreen();

			int id;

			std::cout << "Введите ID студента, которого нужно найти: ";
			std::cin >> id;

			// Отображаем данные студента по ID
			if (!Utils::handleDatabaseOperation([&db, id]() { db.showStudentById(id); })) break;

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '4': // Меняем данные студента
		{
			Utils::clearScreen();

			int id;

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			std::cout << "Введите ID студента, у которого нужно изменить данные: ";
			std::cin >> id;

			// Редактируем данные студента
			if (!Utils::handleDatabaseOperation([&db, id]() { db.editStudentData(db.getStudentById(id)); })) break;

			break;
		}
		case '5': // Удаляем студента
		{
			Utils::clearScreen();

			int id;

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			std::cout << "Введите ID студента, которого нужно удалить: ";
			std::cin >> id;

			// Удаляем студента
			if (!Utils::handleDatabaseOperation([&db, id]() { db.deleteStudent(id); })) break;

			std::cout << "\nСтудент удалён!\n";

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '6': // Выход в главное меню
			Utils::clearScreen();
			break;
		default:
			Utils::clearScreen();
		}
	} while (choice != '6');
}

/*==================== МЕНЮ УПРАВЛЕНИЯ ПРЕДМЕТАМИ ====================*/
void subjectMenu(Database& db)
{
	std::string input;
	char choice;

	do
	{
		std::cout << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "МЕНЮ УПРАВЛЕНИЯ ПРЕДМЕТАМИ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Получить список всех предметов\n";
		std::cout << "2. Добавить новый предмет\n";
		std::cout << "3. Назад\n";

		std::cin >> input;

		// Проверка ввода
		if (input.length() == 1 && input[0] >= '1' && input[0] <= '3')
		{
			choice = input[0];
		}
		else
		{
			choice = '0';
			std::cout << "\nВведите цифру от 1 до 3!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			continue;
		}

		switch (choice)
		{
		case '1': // Получаем список всех предметов
		{
			Utils::clearScreen();

			// Отображаем все предметы
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllSubjects(); })) break;

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '2': // Добавляем новый предмет в список
		{
			Utils::clearScreen();

			int newSubjectId;
			std::string newSubjectName;

			std::cout << "Введите ID нового предмета: ";
			std::cin >> newSubjectId;

			std::cout << "Введите название нового предмета: ";
			std::cin >> newSubjectName;

			// Добавляем предмет в список
			if (!Utils::handleDatabaseOperation([&db, newSubjectId, newSubjectName]() { db.addSubject(newSubjectId, newSubjectName); })) break;
			
			break;
		}
		case '3': // Выход в главное меню
			Utils::clearScreen();
			break;
		default:
			Utils::clearScreen();
		}

	} while (choice != '3');
}

/*==================== МЕНЮ УПРАВЛЕНИЯ ОЦЕНКАМИ ====================*/
void gradesMenu(Database& db)
{
	std::string input;
	char choice;

	do
	{
		std::cout << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "МЕНЮ УПРАВЛЕНИЯ ОЦЕНКАМИ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Поставить оценку студенту\n";
		std::cout << "2. Посмотреть оценки студента\n";
		std::cout << "3. Изменить оценки студента\n";
		std::cout << "4. Удалить оценку\n";
		std::cout << "5. Назад\n";

		std::cin >> input;

		// Проверка ввода
		if (input.length() == 1 && input[0] >= '1' && input[0] <= '5')
		{
			choice = input[0];
		}
		else
		{
			choice = '0';
			std::cout << "\nВведите цифру от 1 до 5!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			continue;
		}

		switch (choice)
		{
		case '1': // Ставим оценку студенту
		{
			Utils::clearScreen();

			int studentId, subjectId, grade;

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			std::cout << "Введите ID студента, которому нужно поставить оценку: ";
			std::cin >> studentId;

			std::cout << "\n";

			// Отображаем все предметы
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllSubjects(); })) break;

			std::cout << "Введите ID предмета, по которому нужно выставить оценку: ";
			std::cin >> subjectId;

			do
			{
				std::cout << "Введите оценку от 0 до 5: ";
				std::cin >> grade;
			} while (grade < 0 || grade > 5); // Проверка, входит ли введённое значение в необходимый диапазон

			// Ставим оценку
			if (!Utils::handleDatabaseOperation([&db, studentId, subjectId, grade]() { db.rate(studentId, subjectId, grade); })) break;

			std::cout << "\nОценка поставлена!\n"; 
			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '2': // Получаем оценки определённого студента
		{
			Utils::clearScreen();

			int id;

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			std::cout << "Введите ID студента, чтобы посмотреть его оценки: ";
			std::cin >> id;
			
			std::cout << "\n";

			// Отображаем данные студента по ID
			if (!Utils::handleDatabaseOperation([&db, id]() { db.showStudentById(id); })) break;

			std::cout << "\n";

			// Отображаем данные о предмете и оценке по нему
			if (!Utils::handleDatabaseOperation([&db, id]() { db.showAllStudentGrades(id); })) break;

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '3': // Редактируем оценку
		{
			Utils::clearScreen();

			int studentId, gradeId;

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			std::cout << "Введите ID студента, у которого нужно изменить оценку: ";
			std::cin >> studentId;

			std::cout << "\n";

			// Отображаем все оценки выбранного студента
			if (!Utils::handleDatabaseOperation([&db, studentId]() { db.showAllStudentGrades(studentId); })) break;

			std::cout << "Введите ID оценки, которую нужно изменить: ";
			std::cin >> gradeId;

			// Получаем оценку по ID и редактируем её
			if (!Utils::handleDatabaseOperation([&db, gradeId]() { db.editGradeData(db.getGradeById(gradeId)); })) break;

			std::cout << "\nОценка обновлена!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '4': // Удаляем оценку
		{
			Utils::clearScreen();

			int studentId, gradeId;

			// Отображаем всех студентов
			if (!Utils::handleDatabaseOperation([&db]() { db.showAllStudents(); })) break;

			std::cout << "Введите ID студента, у которого нужно удалить оценку: ";
			std::cin >> studentId;

			// Отображаем все оценки выбранного студента
			if (!Utils::handleDatabaseOperation([&db, studentId]() { db.showAllStudentGrades(studentId); })) break;

			std::cout << "Введите ID оценки, которую нужно удалить: ";
			std::cin >> gradeId;

			// Удаляем оценку
			if (!Utils::handleDatabaseOperation([&db, gradeId]() { db.deleteGrade(gradeId); })) break;

			std::cout << "\nОценка удалена!\n";
			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '5': // Выход в главное меню
			Utils::clearScreen();
			break;
		default:
			Utils::clearScreen();
		}
	} while (choice != '5');
}