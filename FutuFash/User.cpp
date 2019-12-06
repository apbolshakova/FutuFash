#include "User.h"

map<int, Project*>* User::GetProjects()
{
	return this->projects;
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
	projects.insert(pair<int, Project*>(project->id, project));
}
void User::removeProject(Project* project)
{
	projects.erase(project->id);
}
void User::markToDelete()
{
	this->toDelete = true;
}

