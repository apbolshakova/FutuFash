#pragma once
#include "Common.h"
#include "UserMenu.h"
#include "ProjectsMenu.h"

class Menu;
class User;
class Project;

class MainMenu :
	public Menu
{
private:
	std::map<int, User*> *users;
	std::map<int, Project*> *projects;
	void printMenu();
	void handleUsersMenu();
	void handleProjectsMenu();
	void printProjectsWithParticipants();
	void handleDataSaving();
	void saveProjectsData(std::ofstream& file);
	void saveUsersData(std::ofstream& file);
public:
	MainMenu(std::map<int, User*> *users = nullptr, std::map<int, Project*> *projects = nullptr);
};
