#pragma once
#include "Entities.h"

using namespace std;

int User::getExp()
{
	return this->experienceInYears;
}
map<int, Project*>* User::getProjects()
{
	return this->projects;
}

bool User::isDeleted()
{
	return this->toDelete;
}

void User::setExp(int exp)
{
	try
	{
		if (exp < 0)
			throw exception();
		experienceInYears = exp;
	}
	catch (const exception&)
	{
		cout << "New experience cannot be negative." << endl;
	}
		
}
void User::addProject(Project* project)
{
	this->projects->insert(pair<int, Project*>(project->getId(), project));
}
void User::removeProject(Project* project)
{
	this->projects->erase(project->getId());
}
void User::markToDelete()
{
	this->toDelete = true;
}