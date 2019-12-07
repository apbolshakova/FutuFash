#pragma once
#include "Common.h"

class Entity
{
protected:
	int id;
	std::string name;
public:
	Entity(int id = -1, std::string name = "") : id(id), name(name) {};
	
	int getId() { return this->id; }
	std::string getName() { return this->name; }
	
	void setId(int id);
	void setName(std::string name = "");
};

