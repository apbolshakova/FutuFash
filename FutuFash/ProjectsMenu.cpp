#pragma once
#include "ProjectsMenu.h"

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

		std::cout << "Нажмите номер интересующего вас действия" << endl; 
		opCode = this->getOperationCode(ADDING, SEARCH, exitBtnCode);
		switch (opCode)
		{
		case ADDING: this->handleAdding(); break;
		case PRINT_ALL: this->printAllProjects(); break;
		case SEARCH: this->handleSearch(); break;
		default:
		{
			cout << "Такого запроса не существует";
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ProjectsMenu::printMenu()
{
	cout << "	1- Добавить проект" << endl;
	cout << "	2- Вывести все имеющиеся в базе проекты"<< endl;
	cout << "	3- Поиск по проектам"<< endl;
	cout << "Esc- выход" << endl;
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
	cout << "Заполните, пожалуйста, информацию о проекте" << endl;
	
	cout << "Название проекта";
	string name;
	cin >> name;
	project->setName(name);
	cout << "Дата показа проекта";
	string date;
	cin >> date;
	project->setDate(name);
	cout << "Место показа проекта";
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
	SearchEntityType type = PROJECT;
	SearchHandler Search(type);
	vector<Project*> data = Search.getResult();
	Search.printResult(data);
	cout << "Зайти в профиль в проекта? 1- да, 0- нет";
	bool t;
	cin >> t;
	if (t)
		this->handleProfile(data);
}

Designer* ProjectsMenu::getNewDesigner()
{
	cout << "Имя дизайнера";
	string designer;
	getline(cin,designer);
	SearchEntityType type = SearchEntityType(DESIGNER);
    SearchHandler Search(type);
    vector<Project*> data = Search.getResult(); //делать поиск, пока что-то не найдется
    //Если размер 1 - возвращаешь сам элемени
	//Если размер больше:
	if (data.size == 1)
		return data[0]->getDesigner();
	else
	{
		Search.printResult(data);
		cout << "Выберете номер интересующего вас дизайнера";
		int number;
		cin >> number;

	}
	
}
void ProjectsMenu::handleProfile(vector<Project*> data)
{
	int number = getNumToShow();
	printProfile(data[number]);
	cout << "Вы хотите изменить выбранный проект? 1- да, 0- нет";
	bool t;
	cin >> t;
	if (t)
	{
		cout << "Выберете номер" << endl;
		cout << "1- Изменить количество и состав моделей, 2- Изменить другие позиции, 3- Удалить проект" << endl;
		int k;
		cin >> k;
		if (k == 1)
			handleParticipantsMenu(data[number],this->users);
		else if (k == 2) handleChanging(data[number]);
		else if (k == 3) handleDeleting(data[number]);

	}
}
int ProjectsMenu::getNumToShow()
{

}
void ProjectsMenu::handleParticipantsMenu(Project* project, map<int,User*> *users)
{
	ParticipantsMenu* changeModels;


}
void ProjectsMenu::printProfile(Project* project)
{

}
void ProjectsMenu::handleChanging(Project* project)
{

}
void ProjectsMenu::handleDeleting(Project* project)
{
	project->setStatus(DELETED);
}

ProjectsMenu::~ProjectsMenu()
{
}
