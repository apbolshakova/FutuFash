#include "ProjectsMenu.h"
#include <string>



ProjectsMenu::ProjectsMenu(map<int, Projects*>)
{
	this->*projects;
}
void ProjectsMenu::printMenu()
{
	cout << "������� ����� ������������� ��� ��������";
	cout << "	1- �������� ������";
	cout << "	2- ������� ��� ��������� � ���� �������";
	cout << "	3- ����� �� ��������";
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
		cout << "������ ������� �� ����������";
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
