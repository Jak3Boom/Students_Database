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

	int getId() const { return id; }
	std::string getName() const { return name; }
	std::string getEmail() const { return email; }
	std::string getGroup() const { return group; }

	void setName(std::string newName);
	void setEmail(std::string newEmail);
	void setGroup(std::string newGroup);
};