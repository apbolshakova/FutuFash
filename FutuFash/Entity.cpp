#include "Entity.h"


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