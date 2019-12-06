#pragma once
#include "Common.h"
#include "User.h"
#include "Designer.h"
#include "Model.h"
#include "Menu.h"
using namespace std;
class UserMenu :
	public Menu
{
private:
	map<int, User*> *users;
	enum UserMenuMode {
		GLOBAL_CHANGING,
		PROJECT_CHANGING
	}mode;
	Project* projectToEdit;
	void printMenu();
	//switch
	void handleAdding();
	void printAllUsers();
	void handleSearch();
	//adding
	void addNew(User* user);
	//profile
	int getNumToShow();
	void printProfile(User* user);
	void handleGlobalChanging(User* user);
	void handleGlobalDeleting(User* user);
	void handleProjectAdding(User* user);
	void handleProjectDeleting(User* user);
public:
	UserMenu(map<int, User*> *users, UserMenuMode mode, Project* projectToEdit);
	~UserMenu();
};



