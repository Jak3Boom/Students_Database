#include "Student.h"

int Student::studentIdCounter = 1;

Student::Student(std::string name, std::string email, std::string group)
	: studentId(studentIdCounter++),
	  name(name),
	  email(email),
	  group(group)
{}

void Student::setName(const std::string& newName)
{
	name = newName;
}

void Student::setEmail(const std::string& newEmail)
{
	email = newEmail;
}

void Student::setGroup(const std::string& newGroup)
{
	group = newGroup;
}