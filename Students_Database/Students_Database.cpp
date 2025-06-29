#include <iostream>
#include <vector>

#include "Student.h"

int main()
{
	Student s1("Bum", "bum@gmail.com", "31");
	Student s2("Bem", "bem@gmail.com", "11");
	Student s3("Bam", "bam@gmail.com", "72");
	std::vector<Student> students = { s1, s2, s3 };

	for (Student student : students)
	{

	}

	char choice;
	do
	{
		std::cout << "=== ГЛАВНОЕ МЕНЮ ===\n";
		std::cout << "1. Управление студентами\n";
		std::cout << "2. Управление оценками\n";
		std::cout << "3. Выход\n";

		std::cin >> choice;
	} while (choice != '3');
}