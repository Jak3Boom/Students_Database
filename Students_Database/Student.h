#pragma once
#include <string>

class Student
{
private:
	static int studentIdCounter;
	int studentId;
	std::string name;
	std::string email;
	std::string group;
	
public:
	Student(std::string name, std::string email, std::string group);

	int getId() const { return studentId; }
	std::string getName() const { return name; }
	std::string getEmail() const { return email; }
	std::string getGroup() const { return group; }

	void setName(const std::string& newName);
	void setEmail(const std::string& newEmail);
	void setGroup(const std::string& newGroup);
};