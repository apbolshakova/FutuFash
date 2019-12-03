#include "ProjectsManagementSystem.h"


ProjectsManagementSystem::ProjectsManagementSystem()
{
	std::map<int, User*> users;
	std::map<int, Project*> projects;

	handleDataLoading(&users, &projects);
	handleMainMenu(&users, &projects);
}


void ProjectsManagementSystem::handleDataLoading(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	//TODO
}


void ProjectsManagementSystem::handleMainMenu(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	users->begin();
	try
	{
		//MainMenu(users, projects);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
