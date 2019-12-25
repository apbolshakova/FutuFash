#pragma once
#include "Common.h"
#include "MainMenu.h"

class User;
class Project;
class MainMenu;

class ProjectsManagementSystem
{
private:
	void handleDataLoading(std::map<int, User*> *users, std::map<int, Project*> *projects);
	void handleMainMenu(std::map<int, User*> *users, std::map<int, Project*> *projects);
	void parseProjectsData(std::ifstream& file, std::map<int, Project*> *projects, std::map<int, User*> *users);
	Project* getParsedProject(std::string str, std::map<int, User*> *users);
	void parseUsersData(std::ifstream& file, std::map<int, User*> *users);
	User* getParsedUser(std::string str);
	void bindProjectsToUsers(std::map<int, User*> *users, std::map<int, Project*> *projects);
public:
	ProjectsManagementSystem();
};

