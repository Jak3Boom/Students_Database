#include <iostream>
#include <vector>

#include "Database.h"
#include "Student.h"
#include "Subject.h"
#include "Menu.h"

int main()
{
	Database db;

    db.addStudent("Роман Васильев", "roman.vasiliev@gmail.com", "116");
    db.addStudent("Ирина Новикова", "irina.novikova@gmail.com", "117");
    db.addStudent("Константин Егоров", "konstantin.egorov@gmail.com", "118");
    db.addStudent("Светлана Фролова", "svetlana.frolova@gmail.com", "119");
    db.addStudent("Артём Белов", "artyom.belov@gmail.com", "120");

	db.addSubject(1, "Математика");
    db.addSubject(2, "Физика");
    db.addSubject(3, "Английский язык");
    db.addSubject(4, "Информатика");
    db.addSubject(5, "Химия");

	mainMenu(db);

	return 0;
}