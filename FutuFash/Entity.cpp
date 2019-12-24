#pragma once
#include "Entities.h"

void Entity::setName(std::string name)
{
		if (name.empty()) throw std::exception("New name cannot be empty string.");
		this->name = name;
}
void Entity::setId(int id)
{
		if (id < 0)
			throw std::exception("ID cannot be negative.");
		this->id = id;
}