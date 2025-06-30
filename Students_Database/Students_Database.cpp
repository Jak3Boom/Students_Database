#include <iostream>
#include <vector>

#include "Student.h"
#include "Database.h"
#include "Menu.h"

int main()
{
	Student s1("Bum", "bum@gmail.com", "31");
	Student s2("Bem", "bem@gmail.com", "11");
	Student s3("Bam", "bam@gmail.com", "72");
	std::vector<Student> students = { s1, s2, s3 };

	Database db;

	db.AddStudent(s1);
	db.AddStudent(s2);
	db.AddStudent(s3);

	showMainMenu(db);

	return 0;
}