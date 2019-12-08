#pragma once
#include "Menu.h"
#include "Project.h" 
#include "User.h"
#include <string>
#include <vector>
class ProjectsMenu :
	public Menu
{
private:
	map<int, Project*> *projects;
	map <int, User*> *users;

public:
	ProjectsMenu(map<int, User*> *users, map<int, Project*> *projects);
	void printMenu();
	void handleAdding();
	void printAllProjects();
	void handleSearch();
	void addNew(Project* newProject);
	Designer* getNewDesigner();
	void handleProfile(vector<Project*> data);
	int getNumToShow();
	void printProfile(Project* project);
	void handleChanging(Project* project);
	void handleParticipantsMenu(Project* project);
	void handleDeleting(Project* project);

	~ProjectsMenu();
};

