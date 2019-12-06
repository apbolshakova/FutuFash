#include "ProjectsMenu.h"
#include <string>



ProjectsMenu::ProjectsMenu(map<int, Projects*>)
{
	this->*projects;
}
void ProjectsMenu::printMenu()
{
	cout << "Нажмите номер интересующего вас действия";
	cout << "	1- Добавить проект";
	cout << "	2- Вывести все имеющиеся в базе проекты";
	cout << "	3- Поиск по проектам";
	int number;
	cin >> number;
	switch (number)
	{
	case 1:
		handleAdding();
	case 2:
		printAllProjects();
	case 3:
		handleSearch();
	default:
	{
		cout << "Такого запроса не существует";
		printMenu();
	}

	}
}
void ProjectsMenu::handleAdding()
{
	addNew(Project* project)
	{

	}
}
void ProjectsMenu::handleSearch()
{
	enum Field getField()
	{
		enum Field field;
		return this->field;
	}
	string getQuery()
	{
		string query;
		return query;
	}
	vector<Projects*> getSearchResult(enum ProjectField, string query)
	{

	}
	void printSearchResult(vector<Projects*> result)
	{

	}
}





ProjectsMenu::~ProjectsMenu()
{
}
