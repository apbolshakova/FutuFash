#pragma once
#include "Common.h"
#include "Menu.h"
#include "Entities.h"

class Menu;
class Project;
class User;
class Model;

class ParticipantsMenu :
	public Menu
{
private:
	Project* project;
	std::map<int, User*> *users;
public:
	ParticipantsMenu(std::map<int, User*> *users, Project* project);
	void printMenu();
	void printAllParticipants();
	void changeParticipants();

	~ParticipantsMenu();
};

