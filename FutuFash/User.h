#pragma once
#include "Common.h"
#include "Entity.h"
#include "Entity.cpp"
#include "Project.h"
using namespace std;
class User :
	public Entity
{
private:
	int experienceInYears;
	map<int, Project*> projects;
	bool toDelete;
public:
	User(int experienceInYears = -1, bool toDelete = false) : experienceInYears(experienceInYears), toDelete(toDelete) {};
	map<int, Project*> GetProjects();
	void setExp(int exp);
	void addProject(Project* project, int ProjectId);
	void removeProject(int id);
	void markToDelete();
	~User();
};

