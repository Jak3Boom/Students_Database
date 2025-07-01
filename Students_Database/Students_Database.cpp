#include <iostream>
#include <vector>

#include "Student.h"
#include "Subject.h"
#include "Database.h"
#include "Menu.h"

int main()
{
	Database db;

	Student s1("Bum", "bum@gmail.com", "31");
	Student s2("Bem", "bem@gmail.com", "11");
	Student s3("Bam", "bam@gmail.com", "72");

	db.addStudent(s1);
	db.addStudent(s2);
	db.addStudent(s3);

	Subject math(1, "Математика");
	Subject physics(2, "Физика");
	Subject english(3, "Английский");

	db.addSubject(math);
	db.addSubject(physics);
	db.addSubject(english);

	showMainMenu(db);

	return 0;
}