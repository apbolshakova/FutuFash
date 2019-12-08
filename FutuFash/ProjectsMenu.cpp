#include "ProjectsMenu.h"
#include <string>
#include "Project.h"
#include "SearchHandler.h"
#include "Menu.h"
#include "ParticipantsMenu.h"

using namespace std;
ProjectsMenu::ProjectsMenu(map<int, User*> *users, map<int, Project*> *projects)
{
	this->users = users;
	this->projects = projects;
	if (!users) throw new std::exception("No users structure is found.");
	if (!projects) throw new std::exception("No project structure is found.");
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		this->printMenu();
		enum OpCodes { ADDING = 1, PRINT_ALL, SEARCH };

		std::cout << "������� ����� ������������� ��� ��������" << endl; 
		opCode = Menu*->getOperationCode(ADDING, SEARCH, exitBtnCode);
		switch (opCode)
		{
		case ADDING: this->handleAdding(); break;
		case PRINT_ALL: this->printAllProjects(); break;
		case SEARCH: this->handleSearch(); break;
		default:
		{
			cout << "������ ������� �� ����������";
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ProjectsMenu::printMenu()
{
	cout << "	1- �������� ������" << endl;
	cout << "	2- ������� ��� ��������� � ���� �������"<< endl;
	cout << "	3- ����� �� ��������"<< endl;
	cout << "Esc- �����" << endl;
}
void ProjectsMenu::handleAdding()
{
	system("cls");
	Project* newProject;
	try
	{
		addNew(newProject); //TODO add required data
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	
}
void ProjectsMenu::printAllProjects()
{
	system("cls");
	map <int, Project*> ::iterator it = this->projects->begin();
	for (int i=0; it != this->projects->end(); i++, it++)
		cout << i++ << ") " << it->second->getName() << endl;
}
void ProjectsMenu::addNew(Project* project)
{
	system ("cls");
	cout << "���������, ����������, ���������� � �������" << endl;
	
	cout << "�������� �������";
	string name;
	cin >> name;
	project->setName(name);
	cout << "���� ������ �������";
	string date;
	cin >> date;
	project->setDate(name);
	cout << "����� ������ �������";
	string location;
	cin >> location;
	project->setLocation(name);
	
	Designer* designer = getNewDesigner();
	project->setDesigner*(designer);
	project->setLocation(name);
	map<int, Project*>::iterator it = this->projects->end();
	int key = it->first + 1;
	this->projects->insert(pair< int, Project*>(key, project));
}
void ProjectsMenu::handleSearch()
{
	entityType type = PROJECT;
	SearchHandler* Search(type);
	vector<Project*> data = Search->getSearchResult();
	Search->printSearchResult(data);
	cout << "����� � ������� � �������? 1- ��, 0- ���";
	bool t;
	cin >> t;
	if (t)
		this->handleProfile(data);
}

Designer* ProjectsMenu::getNewDesigner()
{
	cout << "��� ���������";
	string designer;
	getline(cin,designer);
	entityType type = DESIGNER;
    SearchHandler* Search(type);
    vector<Project*> data = Search->getSearchResult(); //������ �����, ���� ���-�� �� ��������
    //���� ������ 1 - ����������� ��� �������
	//���� ������ ������:
	if (data.size == 1)
		return Project*->data[0]->getDesigner();
	else
	{
		Search->printSearchResult(data);
		cout << "�������� ����� ������������� ��� ���������";
		int number;
		cin >> number;

	}
	
}
void ProjectsMenu::handleProfile(vector<Project*> data)
{
	int number = getNumToShow();
	printProfile(project);
	cout << "�� ������ �������� ��������� ������? 1- ��, 0- ���";
	bool t;
	cin >> t;
	if (t)
	{
		cout << "�������� �����" << endl;
		cout << "1- �������� ���������� � ������ �������, 2- �������� ������ �������, 3- ������� ������" << endl;
		int k;
		cin >> k;
		if (k == 1)
			handleParticipantsMenu(project);
		else if (k == 2) handleChanging(project);
		else if (k == 3) handleDeleting(project);

	}
}
void ProjectsMenu::handleParticipantsMenu(Project* project)
{
	ParticipantsMenu* changeModels;


}
void ProjectsMenu::handleChanging(Project* project)
{

}
void ProjectsMenu::handleDeleting(Project* project)
{

}

ProjectsMenu::~ProjectsMenu()
{
}
