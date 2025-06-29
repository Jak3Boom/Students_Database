#include "Student.h"

int Student::idCounter = 1;

Student::Student(std::string name, std::string email, std::string group)
	: id(idCounter++),
	  name(name),
	  email(email),
	  group(group)
{}