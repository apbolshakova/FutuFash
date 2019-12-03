#include "ProjectsManagementSystem.h"


ProjectsManagementSystem::ProjectsManagementSystem()
{
	std::map<int, User*> users;
	std::map<int, Project*> projects;

	try
	{
		handleDataLoading(&users, &projects);
	}
	catch (const std::exception&)
	{
		std::cout << "Unable to load data." << std::endl;
	}
	handleMainMenu(&users, &projects);
}


void ProjectsManagementSystem::handleDataLoading(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	//TODO
}


void ProjectsManagementSystem::handleMainMenu(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	MainMenu(users, projects);
}
