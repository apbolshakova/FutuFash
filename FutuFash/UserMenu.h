#pragma once
#include "Common.h"

class Menu;
class Project;
class User;
class Designer;
class Model;

enum UserMenuMode {
	GLOBAL_CHANGING,
	PROJECT_CHANGING
}mode;
class UserMenu :
	public Menu
{
private:
	std::map<int, User*> *users;
	Project* projectToEdit;
	void printMenu();
	//switch
	void handleAdding();
	void printAllUsers();
	void handleSearch();
	//adding
	//void addNew(User* user);
	void addNew(Designer* designer);
	void addNew(Model* model);
	//profile
	void handleProfile(std::vector<User*> data);
	int getNumToShow(std::vector<User*> data);
	//void printProfile(User* user);
	void printProfile(Designer* designer);
	void printProfile(Model* model);
	void handleGlobalChanging(Designer* designer);
	void handleGlobalChanging(Model* model);
	void handleGlobalDeleting(User* user);
	void handleProjectAdding(User* user); //TODO нужно ли параметр менять на модель
	void handleProjectDeleting(User* user);
public:
	UserMenu(std::map<int, User*> *users, UserMenuMode mode, Project* projectToEdit);
	~UserMenu();
};



