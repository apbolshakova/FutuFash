#pragma once
#include "MainMenu.h"

MainMenu::MainMenu(std::map<int, User*> *users, std::map<int, Project*> *projects)
{
	if (!users) throw new std::exception("No users structure is found.");
	if (!projects) throw new std::exception("No project structure is found.");

	this->users = users;
	this->projects = projects;

	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		this->handleDataSaving();
		this->printMenu();
		enum OpCodes { USERS_MENU = 1, PROJECTS_MENU, PRINT_ALL };

		std::cout << "Press button of required operation." << std::endl;
		opCode = this->getOperationCode(USERS_MENU, PRINT_ALL, exitBtnCode);
		switch (opCode)
		{
		case USERS_MENU: this->handleUsersMenu(); break;
		case PROJECTS_MENU: this->handleProjectsMenu(); break;
		case PRINT_ALL: this->printProjectsWithParticipants();
		default: break;
		}
	} while (opCode != exitBtnCode);
}


void MainMenu::printMenu()
{
	std::cout <<
		"1   - Go to users menu\n" <<
		"2   - Go to projects menu\n" <<
		"3   - Print all projects and users in system\n" <<
		"Esc - Exit" << std::endl;
}


void MainMenu::handleUsersMenu()
{
	try
	{
		UserMenu(this->users, GLOBAL_CHANGING, nullptr); //TODO fix constructor invoke
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


void MainMenu::handleProjectsMenu()
{
	try
	{
		ProjectsMenu(this->users, this->projects); //TODO add required data
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}


void MainMenu::printProjectsWithParticipants()
{
	system("cls");

	if (this->projects->empty())
	{
		std::cout << "No projects in system." << std::endl;
	}
	else
	{
		bool empty = true;
		for (auto const& el : *(this->projects))
		{
			if (el.second->getStatus() == DELETED) continue;
			if (empty) std::cout << "Projects in system: " << std::endl;
			empty = false;
			std::cout << el.first << ". " << el.second->getName() << std::endl;
		}
		if (empty) std::cout << "No projects in system." << std::endl;
	}
	
	if (this->users->empty())
	{
		std::cout << "No users in system." << std::endl;
	}
	else
	{
		bool empty = true;
		for (auto const& el : *(this->users))
		{
			if (el.second->isDeleted()) continue;
			if (empty) std::cout << "Users in system: " << std::endl;
			empty = false;
			std::cout << el.first << ". " << el.second->getName() << std::endl;
		}
		if (empty) std::cout << "No users in system." << std::endl;
	}
	std::cout << "Press any button to return." << std::endl;
	_getch();
}


void MainMenu::handleDataSaving()
{
	std::ofstream file;
	file.open("data.dat");
	this->saveUsersData(file);
	this->saveProjectsData(file);
	file.close();
	std::cout << "Actual information about users and projects was saved." << std::endl;
}

void MainMenu::saveProjectsData(std::ofstream& file)
{
	file << "P\n";
	for (auto const& el : *(this->projects))
	{
		if (el.second->getStatus() == DELETED) continue;

		file << el.first
			<< "%" << el.second->getName()
			<< "%" << el.second->getDate()
			<< "%" << el.second->getLocation()
			<< "%" << el.second->getDesigner()->getId()
			<< "%" << el.second->getModels().size();
		if (el.second->getModels().size() != 0)
		{
			for (auto const& model : el.second->getModels())
				file << "%" << model.first;
		}
		file << "%" << el.second->getStatus();
		file << "%\n";
	}
	file << "P\n";
}

void MainMenu::saveUsersData(std::ofstream& file)
{
	file << "U\n";
	for (auto const& el : *(this->users))
	{
		if (el.second->isDeleted()) continue;

		Designer* elAsDesigner = dynamic_cast<Designer*>(el.second);
		Model* elAsModel = dynamic_cast<Model*>(el.second);

		if (elAsDesigner != nullptr) file << "D%";
		if (elAsModel != nullptr) file << "M%";

		file << el.first
			<< "%" << el.second->getName()
			<< "%" << el.second->getExp();

		if (elAsDesigner != nullptr)
		{
			file << "%" << elAsDesigner->getVogue();
		}

		if (elAsModel != nullptr)
		{
			file << "%" << elAsModel->getHeight()
				<< "%" << elAsModel->getWeight()
				<< "%" << elAsModel->getHairColor();
		}
		file << "%\n";
	}
	file << "U\n";
}