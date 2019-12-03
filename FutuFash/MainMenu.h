#pragma once
#include "Common.h"
#include "Menu.h"
#include "User.h"
#include "Project.h"
#include "UserMenu.h"
#include "ProjectsMenu.h"

class MainMenu :
	public Menu
{
private:
	std::map<int, User*> *users;
	std::map<int, Project*> *projects;
	void printMenu();
	void handleUsersMenu();
	void handleProjectsMenu();
	//void printProjectsWithParticipants(); TODO
	//void handleDataSaving();
public:
	MainMenu(std::map<int, User*> *users, std::map<int, Project*> *projects);
};

