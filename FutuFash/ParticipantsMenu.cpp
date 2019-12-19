#pragma once
#include "ParticipantsMenu.h"
using namespace std;

ParticipantsMenu::ParticipantsMenu(map<int, User*> *users, Project* project)
{
	this->users = users;
	this->project = project;
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		this->printMenu();
		enum OpCodes { PRINTING = 1, CHANGING };

		std::cout << "Choose a number" << endl;
		opCode = this->getOperationCode(PRINTING, CHANGING, exitBtnCode);
		switch (opCode)
		{
		case PRINTING: this->printAllParticipants(); break;
		case CHANGING: this->changeParticipants(); break;
		default:
		{
			cout << "Incorrect number of query"<< endl;
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ParticipantsMenu::printMenu()
{
	cout << "	1- Print all project participants" << endl;
	cout << "	2- Change project participants" << endl;
	cout << "Esc- exit" << endl;

}
void ParticipantsMenu::printAllParticipants()
{
	system("cls");
	map<int, Model*> mapmod = this->project->getModels();
	map <int, Model*> ::iterator it = mapmod.begin();
	for (int i = 0; it != mapmod.end(); i++, it++)
		cout << i++ << ") " << it->second->getName() << endl;
	_getch();
}
void ParticipantsMenu::changeParticipants()
{
	UserMenu(this->users, PROJECT_CHANGING, this->project);
}

ParticipantsMenu::~ParticipantsMenu()
{
}
