#pragma once
#include <string>
#include <vector>

class Subject
{
private:
	int id;
	std::string name;
	
public:
	Subject(int id, const std::string& name);

	int getId() const { return id; }
	std::string getName() const { return name; }
};