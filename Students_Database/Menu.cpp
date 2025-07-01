#include "Menu.h"

// Главное меню
void showMainMenu(Database& db)
{
	char choice;
	do
	{
		std::cout << "=== ГЛАВНОЕ МЕНЮ ===\n\n";
		std::cout << "1. Управление студентами\n";
		std::cout << "2. Управление предметами\n";
		std::cout << "3. Управление оценками\n";
		std::cout << "4. Выход\n";
		std::cin >> choice;

		switch (choice)
		{
		case '1': // Меню управления студентами
			studentMenu(db);
			break;
		case '2': // Меню управления предметами
			subjectMenu(db);
			break;
		case '3': // Меню управления оценками
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
		std::cout << "=== МЕНЮ УПРАВЛЕНИЯ СТУДЕНТАМИ ===\n\n";
		std::cout << "1. Получить список всех студентов\n";
		std::cout << "2. Получить студента по ID\n";
		std::cout << "3. Изменить данные студента\n";
		std::cout << "4. Удалить студента из списка\n";
		std::cout << "5. Назад\n";

		std::cin >> choice;

		switch (choice)
		{
		case '1': // Получаем список всех студентов
			db.showAllStudents();
			break;
		case '2': // Получаем студента по ID
		{
			std::cout << "Введите ID студента, которого нужно найти: ";
			int id;
			std::cin >> id;
			std::cout << "\nID: " << db.getStudentById(id).getId()
				<< " | Имя: " << db.getStudentById(id).getName()
				<< " | Email: " << db.getStudentById(id).getEmail()
				<< " | Группа: " << db.getStudentById(id).getGroup()
				<< "\n\n";
			break;
		}
		case '3': // Меняем данные студента
		{
			std::cout << "Введите ID студента, у которого нужно изменить данные: ";
			int id;
			std::cin >> id;
			db.editStudentData(db.getStudentById(id));
			break;
		}
		case '4': // Удаляем студента
		{
			std::cout << "Введите ID студента, которого нужно удалить: ";
			int id;
			std::cin >> id;
			db.deleteStudent(id);
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
		std::cout << "=== МЕНЮ УПРАВЛЕНИЯ ПРЕДМЕТАМИ ===\n\n";
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

			Subject newSubject(newSubjectId, newSubjectName);
			db.addSubject(newSubject);
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
		std::cout << "=== МЕНЮ УПРАВЛЕНИЯ ОЦЕНКАМИ ===\n\n";
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

			try
			{
				db.rate(studentId, subjectId, grade);
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "Ошибка: " << e.what() << "\n\n";
			}
			catch (const std::out_of_range& e)
			{
				std::cerr << "Ошибка: " << e.what() << "\n\n";
			}
			break;
		}
		case '2': // Получаем оценки определённого студента
		{
			std::cout << "Введите ID студента, чтобы посмотреть его оценки: ";
			int id;
			std::cin >> id;

			std::cout << "\nДанные студента:";
			db.showStudentById(id); // Отображаем данные студента по ID

			// Выводим данные о предмете и оценке по нему
			try
			{
				std::cout << "========================================\n\n";
				for (const StudentGrade& data : db.getStudentGradesById(id))
				{
					std::cout << std::format("ID предмета: {}\n"
						"Предмет: {}\n"
						"Оценка: {}\n"
						"Дата: {}\n\n", data.getSubjectId(), data.getSubjectName(), data.getGrade(), data.getDate());
				}
				std::cout << "========================================\n\n";
			}
			catch (const std::runtime_error& e)
			{
				std::cerr << e.what() << std::endl;
			}
			break;
		}
		case '3': // Меняем оценку
		{
			std::cout << "Введите ID студента, у которого нужно изменить оценку: ";
			int id;
			std::cin >> id;
			//
			break;
		}
		case '4': // Удаляем оценку
		{
			std::cout << "Введите ID студента, у которого нужно удалить оценку: ";
			int id;
			std::cin >> id;
			//
			break;
		}
		case '5':
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}
	} while (choice != '5');
}