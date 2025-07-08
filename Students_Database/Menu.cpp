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

		std::cout << "1. Получить список всех студентов\n";
		std::cout << "2. Получить студента по ID\n";
		std::cout << "3. Изменить данные студента\n";
		std::cout << "4. Удалить студента из списка\n";
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
		case '1': // Получаем список всех студентов
		{
			Utils::clearScreen();

			// Отображаем всех студентов
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '2': // Получаем студента по ID
		{
			Utils::clearScreen();

			int id;

			std::cout << "Введите ID студента, которого нужно найти: ";
			std::cin >> id;

			// Отображаем данные студента по ID
			try { db.showStudentById(id); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '3': // Меняем данные студента
		{
			Utils::clearScreen();

			int id;

			// Отображаем всех студентов
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID студента, у которого нужно изменить данные: ";
			std::cin >> id;

			// Редактируем данные студента
			try { db.editStudentData(db.getStudentById(id)); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			break;
		}
		case '4': // Удаляем студента
		{
			Utils::clearScreen();

			int id;

			// Отображаем всех студентов
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID студента, которого нужно удалить: ";
			std::cin >> id;

			// Удаляем студента
			try { db.deleteStudent(id); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "\nСтудент удалён!\n";

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
			try { db.showAllSubjects(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет предметов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

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
			try { db.addSubject(newSubjectId, newSubjectName); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректных данных
			{
				std::cerr << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			
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
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID студента, которому нужно поставить оценку: ";
			std::cin >> studentId;

			std::cout << "\n";

			// Отображаем все предметы
			try { db.showAllSubjects(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет предметов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID предмета, по которому нужно выставить оценку: ";
			std::cin >> subjectId;

			do
			{
				std::cout << "Введите оценку от 0 до 5: ";
				std::cin >> grade;
			} while (grade < 0 || grade > 5); // Проверка, входит ли введённое значение в необходимый диапазон

			// Ставим оценку
			try
			{
				db.rate(studentId, subjectId, grade);
				std::cout << "\nОценка поставлена!\n";
			}
			catch (const std::invalid_argument& e) // Обработка ввода некорректных данных
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '2': // Получаем оценки определённого студента
		{
			Utils::clearScreen();

			int id;

			// Отображаем всех студентов
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID студента, чтобы посмотреть его оценки: ";
			std::cin >> id;
			
			std::cout << "\n";

			// Отображаем данные студента по ID
			try { db.showStudentById(id); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "\n";

			// Отображаем данные о предмете и оценке по нему
			try { db.showAllStudentGrades(id); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			Utils::pauseScreen();
			Utils::clearScreen();
			break;
		}
		case '3': // Редактируем оценку
		{
			Utils::clearScreen();

			int studentId, gradeId;

			// Отображаем всех студентов для выбора
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID студента, у которого нужно изменить оценку: ";
			std::cin >> studentId;

			std::cout << "\n";

			// Отображаем все оценки выбранного студента
			try { db.showAllStudentGrades(studentId); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range &e) // Обработка ситуации, когда у студента нет оценок
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID оценки, которую нужно изменить: ";
			std::cin >> gradeId;

			// Получаем оценку по ID и редактируем её
			try { db.editGradeData(db.getGradeById(gradeId)); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, если введённые данные отсутствуют
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

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
			try { db.showAllStudents(); }
			catch (const std::out_of_range& e) // Обработка ситуации, когда в списке нет студентов
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID студента, у которого нужно удалить оценку: ";
			std::cin >> studentId;

			// Отображаем все оценки выбранного студента
			try { db.showAllStudentGrades(studentId); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, когда у студента нет оценок
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

			std::cout << "Введите ID оценки, которую нужно удалить: ";
			std::cin >> gradeId;

			// Удаляем оценку
			try { db.deleteGrade(gradeId); }
			catch (const std::invalid_argument& e) // Обработка ввода некорректного ID
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}
			catch (const std::out_of_range& e) // Обработка ситуации, когда оценка с таким ID не найдена
			{
				std::cerr << "\n" << e.what();
				Utils::pauseScreen();
				Utils::clearScreen();
				break;
			}

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