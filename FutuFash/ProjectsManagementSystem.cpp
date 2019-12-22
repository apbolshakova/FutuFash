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
	if (file.eof())
	{
		file.close();
		return;
	}
	try
	{
		parseUsersData(file, users);
		parseProjectsData(file, projects);
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


void ProjectsManagementSystem::parseProjectsData(std::ifstream& file, std::map<int, Project*> *projects)
{
	std::string str;
	std::getline(file, str);
	if (str != "P") throw new std::exception("Data file is corrupted and will be deleted.");
	std::getline(file, str);
	while (str != "P")
	{
		Project* project = getParsedProject(str);
		projects->insert(std::pair< int, Project*>(project->getId(), project));
		std::getline(file, str);
	}
}


Project* ProjectsManagementSystem::getParsedProject(std::string str) 
{
	char delim = '%';
	Project* project = new Project();

	std::size_t startPos = 0;
	std::size_t endPos = str.find(startPos, delim);
	project->setId(stoi(str.substr(startPos, endPos - startPos)));
	
	startPos = endPos + 1;
	endPos = str.find(startPos, delim);
	project->setName(str.substr(startPos, endPos - startPos));
	
	startPos = endPos + 1;
	endPos = str.find(startPos, delim);
	project->setDate(str.substr(startPos, endPos - startPos));

	startPos = endPos + 1;
	endPos = str.find(startPos, delim);
	project->setLocation(str.substr(startPos, endPos - startPos));

	startPos = endPos + 1;
	endPos = str.find(startPos, delim);
	//project->setDesigner(stoi(str.substr(startPos, endPos - startPos))); TODO finish
}


void ProjectsManagementSystem::parseUsersData(std::ifstream& file, std::map<int, User*> *users)
{
	std::string str;
	std::getline(file, str);
	if (str != "U") throw new std::exception("Data file is corrupted and will be deleted.");
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
	char delim = '%';
	std::size_t startPos = 0;
	std::size_t endPos = str.find(startPos, delim);
	std::string type = str.substr(startPos, endPos - startPos);
	if (type == "D")
	{
		Designer* user = new Designer();
		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setId(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setName(str.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setExp(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setVogue(str.substr(startPos, endPos - startPos));

		return user;
	}
	else if (type == "M")
	{
		Model* user = new Model();
		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setId(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setName(str.substr(startPos, endPos - startPos));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setExp(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setHeight(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setWeight(stoi(str.substr(startPos, endPos - startPos)));

		startPos = endPos + 1;
		endPos = str.find(startPos, delim);
		user->setHairColor(str.substr(startPos, endPos - startPos));

		return user;
	}
	else throw new std::exception("Corrupted user data.");
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
