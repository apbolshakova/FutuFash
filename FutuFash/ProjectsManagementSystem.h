#pragma once
#include "Common.h"

class ProjectsManagementSystem
{
public:
	ProjectsManagementSystem();
	void handleDataLoading(std::map<int, User> *users, std::map<int, Project> *projects);
	void handleMainMenu(std::map<int, User> *users, std::map<int, Project> *projects);
};

