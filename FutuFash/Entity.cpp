#pragma once
#include "Entities.h"

void Entity::setName(std::string name)
{
	try
	{
		if (name.empty()) throw std::exception();
		this->name = name;
	}
	catch (const std::exception&)
	{
		std::cout << "New name cannot be empty string." << std::endl;
	}
}
void Entity::setId(int id)
{
	try
	{
		if (id < 0)
			throw std::exception();
		this->id = id;
	}
	catch (const std::exception&)
	{
		std::cout << "ID cannot be negative." << std::endl;
	}
}