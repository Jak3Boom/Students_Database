#include "Menu.h"

// Отображаем главное меню
void showMainMenu(Database& db)
{
	char choice;
	do
	{
		std::cout << "=== ГЛАВНОЕ МЕНЮ ===\n";
		std::cout << "1. Управление студентами\n";
		std::cout << "2. Управление оценками\n";
		std::cout << "3. Выход\n";
		std::cin >> choice;

		switch (choice)
		{
		case '1': // Меню управления студентами
			studentMenu(db);
			break;
		case '2': // Меню управления оценками
			gradesMenu(db);
			break;
		case '3':
			std::cout << "До свидания!\n";
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}

	} while (choice != '3');
}

// Отображаем меню управления студентами
void studentMenu(Database& db)
{
	char choice;
	do
	{
		std::cout << "=== МЕНЮ УПРАВЛЕНИЯ СТУДЕНТАМИ ===\n";
		std::cout << "1. Получить список всех студентов\n";
		std::cout << "2. Получить студента по ID\n";
		std::cout << "3. Изменить данные студента\n";
		std::cout << "4. Удалить студента из списка\n";
		std::cout << "5. Назад\n";

		std::cin >> choice;

		switch (choice)
		{
		case '1': // Получаем список всех студентов
			db.GetAllStudents();
			break;
		case '2': // Получаем студента по ID
			std::cout << "Введите ID студента, которого нужно найти: ";
			int findId;
			std::cin >> findId;
			std::cout << "\nID: " << db.GetStudentById(findId).getId()
				<< " | Имя: " << db.GetStudentById(findId).getName()
				<< " | Email: " << db.GetStudentById(findId).getEmail()
				<< " | Группа: " << db.GetStudentById(findId).getGroup()
				<< "\n\n";
			break;
		case '3': // Меняем данные студента
			std::cout << "Введите ID студента, у которого нужно изменить данные: ";
			int editId;
			std::cin >> editId;
			db.EditStudentData(db.GetStudentById(editId));
			break;
		case '4': // Удаляем студента
			std::cout << "Введите ID студента, которого нужно удалить: ";
				int deleteId;
				std::cin >> deleteId;
				db.DeleteStudent(deleteId);
			break;
		case '5':
			break;
		default:
			std::cout << "Такого варианта нет!\n";
		}
	} while (choice != '5');
}

// Отображаем меню управления оценками
void gradesMenu(Database& db)
{
}