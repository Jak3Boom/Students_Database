#include <iostream>
#include <vector>

#include "Student.h"
#include "Subject.h"
#include "Database.h"
#include "Menu.h"

int main()
{
	Database db;

	db.addStudent("Bum", "bum@gmail.com", "31");
	db.addStudent("Bem", "bem@gmail.com", "11");
	db.addStudent("Bam", "bam@gmail.com", "72");

	db.addSubject(1, "Математика");
	db.addSubject(2, "Физика");
	db.addSubject(3, "Английский");

	mainMenu(db);

	return 0;
}