#pragma once
#include <string>

class Student
{
private:
	static int idCounter;
	int id;
	std::string name;
	std::string email;
	std::string group;
	
public:
	Student(std::string name, std::string email, std::string group);
	int getId() { return id; }
	std::string getName() { return name; }
	std::string getEmail() { return email; }
	std::string getGroup() { return group; }
};