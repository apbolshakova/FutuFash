#pragma once
#include "Common.h"
#include "Menu.h"
#include "Project.h"
#include "User.h"
class ParticipantsMenu :
	public Menu
{
private:
	Project* project;
	map<int, User*> *users;
public:
	ParticipantsMenu(map<int, User*> *users, Project* project);
	void printMenunow();
	void printAllParticipants();
	void changeParticipants();

	~ParticipantsMenu();
};

