#include "MainMenu.h"


MainMenu::MainMenu(std::map<int, User*> *users = nullptr, std::map<int, Project*> *projects = nullptr)
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
		this->printMenu();
		enum OpCodes { USERS_MENU = 1, PROJECTS_MENU, PRINT_ALL, SAVE };

		std::cout << "Press button of required operation." << std::endl;
		opCode = this->getOperationCode(USERS_MENU, SAVE, exitBtnCode);
		switch (opCode)
		{
		case USERS_MENU: this->handleUsersMenu(); break;
		case PROJECTS_MENU: this->handleProjectsMenu(); break;
		case PRINT_ALL: this->printProjectsWithParticipants(); break;
		case SAVE: this->handleDataSaving();
		default: break;
		}

	} while (opCode != exitBtnCode);
}


void MainMenu::printMenu()
{
	system("cls");
	std::cout <<
		"1   - Go to users menu\n" <<
		"2   - Go to projects menu\n" <<
		"3   - Print all projects and users in system\n" <<
		"4   - Save current system state\n" <<
		"Esc - Exit" << std::endl;
}


void MainMenu::handleUsersMenu()
{
	try
	{
		UserMenu(); //TODO add required data
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
		ProjectsMenu(); //TODO add required data
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
		std::cout << "Projects in system: " << std::endl;
		for (auto const& el : *(this->projects))
		{
			std::cout << el.first << '. ' << el.second->getName() << std::endl;
		}
	}
	
	if (this->users->empty())
	{
		std::cout << "No users in system." << std::endl;
	}
	else
	{
		std::cout << "Users in system: " << std::endl;
		for (auto const& el : *(this->users))
		{
			std::cout << el.first << '. ' << el.second->getName() << std::endl;
		}
	}
	std::cout << "Press any button to return." << std::endl;
	_getch();
}


void MainMenu::handleDataSaving()
{
	//TODO
}