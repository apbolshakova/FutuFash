#include "User.h"

map<int, Project*> User::GetProjects()
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
void User::addProject(Project* project, int ProjectId)
{
	projects.insert(pair<int, Project*>(ProjectId, project));
}
void User::removeProject(int id)
{
	projects.erase(id);
}
void User::markToDelete()
{
	//if (toDelete)
		//?
}
User::User()
{
}


User::~User()
{
}
