#include <iostream>
#include <vector>

#include "Database.h"
#include "Student.h"
#include "Subject.h"
#include "Menu.h"

int main()
{
	Database db;

    db.loadFromFiles();

	mainMenu(db);

    db.saveToFiles();

	return 0;
}