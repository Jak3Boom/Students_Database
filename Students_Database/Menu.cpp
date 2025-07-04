#include "Menu.h"
#include "Utils.h"

// Главное меню
void mainMenu(Database& db)
{
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
		std::cin >> choice;

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
		case '4':
			std::cout << "До свидания!\n";
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}

	} while (choice != '4');
}

// Меню управления студентами
void studentMenu(Database& db)
{
	char choice;
	do
	{
		std::cout << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "МЕНЮ УПРАВЛЕНИЯ СТУДЕНТАМИ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Получить список всех студентов\n";
		std::cout << "2. Получить студента по ID\n";
		std::cout << "3. Изменить данные студента\n";
		std::cout << "4. Удалить студента из списка\n";
		std::cout << "5. Назад\n";

		std::cin >> choice;

		switch (choice)
		{
		case '1': // Получаем список всех студентов
		{
			Utils::clearScreen();

			db.showAllStudents();

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '2': // Получаем студента по ID
		{
			Utils::clearScreen();

			std::cout << "Введите ID студента, которого нужно найти: ";
			int id;
			std::cin >> id;

			std::cout << "\n" << std::string(80, '=') << "\n";
			std::cout << std::format("{:^80}\n", "ДАННЫЕ СТУДЕНТА");
			std::cout << std::string(80, '=');
			db.showStudentById(id); // Отображаем данные студента по ID
			std::cout << std::string(80, '=') << "\n";

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '3': // Меняем данные студента
		{
			Utils::clearScreen();

			std::cout << "Введите ID студента, у которого нужно изменить данные: ";
			int id;
			std::cin >> id;

			std::cout << "\n";
			db.editStudentData(db.getStudentById(id));

			Utils::clearScreen();
			break;
		}
		case '4': // Удаляем студента
		{
			std::cout << "Введите ID студента, которого нужно удалить: ";
			int id;
			std::cin >> id;
			db.deleteStudent(id);

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '5':
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}
	} while (choice != '5');
}

// Меню управления предметами
void subjectMenu(Database& db)
{
	char choice;
	do
	{
		std::cout << "\n" << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "МЕНЮ УПРАВЛЕНИЯ ПРЕДМЕТАМИ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Получить список всех предметов\n";
		std::cout << "2. Добавить новый предмет\n";
		std::cout << "3. Назад\n";

		std::cin >> choice;

		switch (choice)
		{
		case '1': // Получаем список всех предметов
			db.showAllSubjects();
			break;
		case '2': // Добавляем новый предмет в список
		{
			int newSubjectId;
			std::string newSubjectName;

			std::cout << "Введите ID нового предмета: ";
			std::cin >> newSubjectId;

			std::cout << "Введите название нового предмета: ";
			std::cin >> newSubjectName;

			db.addSubject(newSubjectId, newSubjectName);
			break;
		}
		case '3':
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}

	} while (choice != '3');
}

// Меню управления оценками
void gradesMenu(Database& db)
{
	char choice;
	do
	{
		std::cout << "\n" << std::string(80, '=') << "\n";
		std::cout << std::format("{:^80}\n", "МЕНЮ УПРАВЛЕНИЯ ОЦЕНКАМИ");
		std::cout << std::string(80, '=') << "\n";

		std::cout << "1. Поставить оценку студенту\n";
		std::cout << "2. Посмотреть оценки студента\n";
		std::cout << "3. Изменить оценки студента\n";
		std::cout << "4. Удалить оценку\n";
		std::cout << "5. Назад\n";

		std::cin >> choice;

		switch (choice)
		{
		case '1': // Ставим оценку студенту
		{
			int studentId;
			int subjectId;
			int grade;

			db.showAllStudents(); // Отображаем всех студентов
			std::cout << "Введите ID студента, которому нужно поставить оценку: ";
			std::cin >> studentId;

			std::cout << "\n";
			db.showAllSubjects(); // Отображаем все предметы
			std::cout << "Введите ID предмета, по которому нужно выставить оценку: ";
			std::cin >> subjectId;

			do
			{
				std::cout << "Введите оценку от 0 до 5: ";
				std::cin >> grade;
			} while (grade < 0 || grade > 5); // Проверка, входит ли введённое значение в необходимый диапазон

			db.rate(studentId, subjectId, grade); // Ставим оценку
			break;
		}
		case '2': // Получаем оценки определённого студента
		{
			std::cout << "Введите ID студента, чтобы посмотреть его оценки: ";
			int id;
			std::cin >> id;

			std::cout << "\n" << std::string(80, '=') << "\n";
			std::cout << std::format("{:^80}\n", "ДАННЫЕ СТУДЕНТА");
			std::cout << std::string(80, '=');
			db.showStudentById(id); // Отображаем данные студента по ID
			std::cout << std::string(80, '=') << "\n";
			try
			{
				db.showAllStudentGrades(id); // Выводим данные о предмете и оценке по нему
			}
			catch (const std::out_of_range& e) // Обработка ситуации, когда у студента нет оценок
			{
				std::cerr << "\n" << e.what();
			}

			Utils::pauseScreen();
			break;
		}
		case '3': // Меняем оценку
		{
			int studentId;
			int gradeId;

			db.showAllStudents(); // Отображаем всех студентов для выбора
			std::cout << "Введите ID студента, у которого нужно изменить оценку: ";
			std::cin >> studentId;

			try
			{
				db.showAllStudentGrades(studentId); // Отображаем все оценки выбранного студента
			}
			catch (const std::out_of_range &e) // Обработка ситуации, когда у студента нет оценок
			{
				std::cerr << "\nОшибка: " << e.what();
				break; // Выход из case, если нет оценок
			}

			std::cout << "Введите ID оценки, которую нужно изменить: ";
			std::cin >> gradeId;

			try
			{
				db.editGradeData(db.getGradeById(gradeId)); // Получаем оценку по ID и изменяем её
			}
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\nОшибка: " << e.what();
			}
			catch (const std::out_of_range& e) // Обработка ситуации, когда оценка с таким ID не найдена
			{
				std::cerr << "\nОшибка: " << e.what();
			}
			break;
		}
		case '4': // Удаляем оценку
		{
			int studentId;
			int gradeId;

			db.showAllStudents(); // Отображаем всех студентов для выбора
			std::cout << "Введите ID студента, у которого нужно удалить оценку: ";
			std::cin >> studentId;

			try
			{
				db.showAllStudentGrades(studentId); // Отображаем все оценки выбранного студента
			}
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\nОшибка: " << e.what();

				Utils::pauseScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, когда у студента нет оценок
			{
				std::cerr << "\nОшибка: " << e.what();

				Utils::pauseScreen();
				break;
			}

			std::cout << "Введите ID оценки, которую нужно удалить: ";
			std::cin >> gradeId;

			try
			{
				db.deleteGradeById(gradeId); // Удаляем оценку
			}
			catch (const std::out_of_range& e) // Обработка ситуации, когда оценка с таким ID не найдена
			{
				std::cerr << "\nОшибка: " << e.what();

				Utils::pauseScreen();
			}
			break;
		}
		case '5':
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}
	} while (choice != '5');
}