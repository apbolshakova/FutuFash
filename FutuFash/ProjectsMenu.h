#pragma once
#include "Menu.h"
#include "Project.h"
#include <string>
#include <vector>
using namespace std;
class ProjectsMenu :
	public Menu
{
private:
	map<int, Project*> *projects;


public:
	ProjectsMenu();
	void printMenu();
	void handleAdding();
	void printAllProjects();
	void handleSearch();
	void addNew(Project* project);



	~ProjectsMenu();
};

