#pragma once
#include "Menu.h"
#include <string>
using namespace std;
class ProjectsMenu :
	public Menu
{
private:
	map<int, Projects*> *projects;


public:
	ProjectsMenu();
	void printMenu();
	void handleAdding();
	void printAllProjects();
	void handleSearch();
	void addNew(Project* project);
	enum Field getField();
	string getQuery();
	void getSearchResult(enum ProjectField field, string query);
	void printSearchResult(vector<Projects*> result);


	~ProjectsMenu();
};

