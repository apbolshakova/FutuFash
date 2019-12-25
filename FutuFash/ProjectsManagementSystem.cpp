#pragma once
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
	std::ifstream file;
	file.open("data.dat");
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		file.close();
		return;
	}
	try
	{
		parseUsersData(file, users);
		parseProjectsData(file, projects, users);
		bindProjectsToUsers(users, projects);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		file.close();
		std::remove("data.dat");
		std::cout << "Please restart the program. Press any button to quit." << std::endl;
		_getch();
	}
	file.close();
}


void ProjectsManagementSystem::parseProjectsData(std::ifstream& file, std::map<int, Project*> *projects, std::map<int, User*> *users)
{
	std::string str;
	std::getline(file, str);
	if (str != "P") throw std::exception("Data file is corrupted and will be deleted.");
	std::getline(file, str);
	while (str != "P")
	{
		Project* project = getParsedProject(str, users);
		if (project != nullptr)
		    projects->insert(std::pair< int, Project*>(project->getId(), project));
		std::getline(file, str);
	}
}


Project* ProjectsManagementSystem::getParsedProject(std::string str, std::map<int, User*> *users)
{
	char delim = '%';
	Project* project = new Project();

	std::size_t startPos = 0;
	std::size_t endPos = str.find(delim, startPos);
	project->setId(stoi(str.substr(startPos, endPos - startPos)));

	startPos = endPos + 1;
	endPos = str.find(delim, startPos);
	project->setName(str.substr(startPos, endPos - startPos));

	startPos = endPos + 1;
	endPos = str.find(delim, startPos);
	project->setDate(str.substr(startPos, endPos - startPos));

	startPos = endPos + 1;
	endPos = str.find(delim, startPos);
	project->setLocation(str.substr(startPos, endPos - startPos));

	startPos = endPos + 1;
	endPos = str.find(delim, startPos);
	int designerId = stoi(str.substr(startPos, endPos - startPos));
	if (users->count(designerId) == 0) project->setDesigner(nullptr);
	else project->setDesigner(dynamic_cast<Designer*>((*users)[designerId]));

	startPos = endPos + 1;
	endPos = str.find(delim, startPos);
	int modelsNum = stoi(str.substr(startPos, endPos - startPos));
	for (int i = 0; i < modelsNum; i++)
	{
		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		int modelId = stoi(str.substr(startPos, endPos - startPos));
		if (users->count(modelId) != 0)
			project->addModel(dynamic_cast<Model*>((*users)[modelId]));
	}

	startPos = endPos + 1;
	endPos = str.find(delim, startPos);
	ProjectStatus status = ProjectStatus(stoi(str.substr(startPos, endPos - startPos)));
	if (status == DELETED)
	{
		free(project);
		return nullptr;
	}
	project->setStatus(status);
	return project;
}


void ProjectsManagementSystem::parseUsersData(std::ifstream& file, std::map<int, User*> *users)
{
	std::string str;
	std::getline(file, str);
	if (str != "U") throw std::exception("Data file is corrupted and will be deleted.");
	std::getline(file, str);
	while (str != "U")
	{
		User* user = getParsedUser(str);
		users->insert(std::pair< int, User*>(user->getId(), user));
		std::getline(file, str);
	}
}


User* ProjectsManagementSystem::getParsedUser(std::string str)
{
	std::string delim = "%";
	std::size_t startPos = 0;
	std::size_t endPos = str.find(delim, startPos);
	std::string type = str.substr(startPos, endPos - startPos);
	if (type == "D")
	{
		Designer* user = new Designer();
		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setId(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setName(str.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setExp(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setVogue(str.substr(startPos, endPos - startPos));

		return user;
	}
	else if (type == "M")
	{
		Model* user = new Model();
		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setId(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setName(str.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setExp(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setHeight(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setWeight(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(delim, startPos);
		user->setHairColor(str.substr(startPos, endPos - startPos));

		return user;
	}
	else throw std::exception("Corrupted user data.");
}


void ProjectsManagementSystem::bindProjectsToUsers(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	for (auto const& project : *projects)
	{
		project.second->getDesigner()->addProject(project.second);
		std::map<int, Model*> models = project.second->getModels();
		for (auto const& model : models)
		{
			model.second->addProject(project.second);
		}
	}
}


void ProjectsManagementSystem::handleMainMenu(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	try
	{
		MainMenu(users, projects);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
