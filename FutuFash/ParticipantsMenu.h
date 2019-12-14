#pragma once
#include "Common.h"
#include "Menu.h"
#include "Project.h"
class ParticipantsMenu :
	public Menu
{
private:
	Project* project;
	map <int, User*> *users;
public:
	ParticipantsMenu( map < int,User*> *users , Project* project );

	~ParticipantsMenu();
};

