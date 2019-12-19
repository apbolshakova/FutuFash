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
		cout << "Select a number" << endl;
		this->printMenu();
		enum OpCodes { ADDING = 1, PRINT_ALL, SEARCH };

		
		opCode = this->getOperationCode(ADDING, SEARCH, exitBtnCode);
		switch (opCode)
		{
		case ADDING: this->handleAdding(); break;
		case PRINT_ALL: this->printAllProjects(); break;
		case SEARCH: this->handleSearch(); break;
		default:
		{
			cout << "Incorrect number of query"<< endl;
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ProjectsMenu::printMenu()
{
	cout << "	1- Add a project" << endl;
	cout << "	2- Print all projects in base"<< endl;
	cout << "	3- Search in project base"<< endl;
	cout << "Esc- Exit" << endl;
}
void ProjectsMenu::handleAdding()
{
	system("cls");
	;
	try
	{
		addNew();
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
		cout << ++i << ") " << it->second->getName() << endl;
}
void ProjectsMenu::addNew()
{
	Project* project = new Project();
	system ("cls");
	cout << "Insert the information about new project" << endl;
	
	cout << "Project name"<< endl;
	string name;
	cin >> name;
	project->setName(name);
	cout << "Date of show"<< endl;
	string date;
	cin >> date;
	project->setDate(date);
	cout << "Location"<< endl;
	string location;
	cin >> location;
	project->setLocation(location);
	project->setStatus(INSEARCH);
	Designer* designer = getNewDesigner();
	project->setDesigner(designer);
	project->setLocation(name);
	map<int, Project*>::iterator it = this->projects->end();
	int key = 1;
	if (this->projects->size() != 0)
	{
		key = it->first + 1;
	}
	project->setId(key);
	this->projects->insert(pair< int, Project*>(key, project));
}
void ProjectsMenu::handleSearch()
{
	SearchEntityType type = PRJ;
	SearchHandler Search(type);
	//vector<Project*> data = Search.getResult();
	//Search.printResult(data);
	vector<Project*> data;
	Project* item = (*this->projects)[1];
	data.push_back(item);
	cout << "Do you want to work with particular profile? 1- yes, 0- no"<< endl;
	bool t;
	cin >> t;
	if (t) this->handleProfile(data); //TODO передавать результат поиска
}

Designer* ProjectsMenu::getNewDesigner()
{
	cout << "Name of designer"<< endl;
	string designer;
	getline(cin,designer);
	SearchEntityType type = DSG;
    SearchHandler Search(type);
    //vector<Project*> data = Search.getResult(); //делать поиск, пока что-то не найдется
    //Если размер 1 - возвращаешь сам элемени
	//Если размер больше:
	//if (data.size == 1)
	//	return data[0]->getDesigner();
	//else
	//{
	//	Search.printResult(data);
	//	cout << "Выберете номер интересующего вас дизайнера";
	//	int number;
	//	cin >> number;

    //	}
	return nullptr;
}
void ProjectsMenu::handleProfile(vector<Project*> data)
{
	int number = getNumToShow(data.size());
	printProfile(data[number]);
	cout << "Do you want to change this project? 1- yes, 0- no"<< endl;
	bool t;
	cin >> t;
	if (t)
	{
		cout << "Choose the number" << endl;
		cout << "1- Change models, 2- Change other positions, 3- Delete this project" << endl;
		int k;
		cin >> k;
		if (k == 1)
			handleParticipantsMenu(data[number],this->users);
		else if (k == 2) handleChanging(data[number]);
		else if (k == 3) handleDeleting(data[number]);

	}
}
int ProjectsMenu::getNumToShow(int size)
{
	cout << "What project to show? 0- first, " << size-1 << "- last"<< endl;
	int p; cin >> p;
	return p; 
}
void ProjectsMenu::handleParticipantsMenu(Project* project, map<int,User*> *users)
{
	ParticipantsMenu(users, project);
}

void ProjectsMenu::printProfile(Project* project)
{
	cout << "Name of project : " << project->getName() << endl;
	cout << "   Date of show : " << project->getDate() << endl;
	cout << "   Location : " << project->getLocation() << endl;
	cout << "   Name of designer : " << project->getDesigner() << endl;
	cout << "   Project status : " << project->getStatus() << endl;
	cout << "   Number of models" << project->getModels().size() << endl;
	cout << endl;
}

void ProjectsMenu::handleChanging(Project* project)
{
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		cout << "Select a number" << endl;
		enum OpCodes { NAME = 1, DATE, LOCATION, STATUS };
		cout << "   1- change project name" << endl;
		cout << "   2- change date of show" << endl;
		cout << "   3- change location" << endl;
		cout << "   4- change project status" << endl;
		opCode = this->getOperationCode(NAME, STATUS, exitBtnCode);
		switch (opCode)
		{
		case NAME: this->changeName(project); break;
		case DATE: this->changeDate(project); break;
		case LOCATION: this->changeLocation(project); break;
		case STATUS: this->changeStatus(project); break;
		default:
		{
			cout << "Incorrect number of query"<< endl;
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ProjectsMenu::changeName(Project* project)
{
	string newname; getline(cin,newname);
	project->setName(newname);
}
void ProjectsMenu::changeDate(Project* project)
{
	string newdate; getline(cin, newdate);
	project->setName(newdate);
}
void ProjectsMenu::changeLocation(Project* project)
{
	string newlocation; getline(cin, newlocation);
	project->setName(newlocation);
}
void ProjectsMenu::changeStatus(Project* project)
{
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		cout << "Select a number" << endl;
		enum OpCodes { IN = 1, FIL, FIN};
		cout << "   1- in search of models" << endl;
		cout << "   2- waiting for show" << endl;
		cout << "   3- the show is finished" << endl;
		opCode = this->getOperationCode(IN, FIN, exitBtnCode);
		switch (opCode)
		{
		case IN: project->setStatus(INSEARCH); break;
		case FIL: project->setStatus(FILLED); break;
		case FIN: project->setStatus(FINISHED); break;
		default:
		{
			cout << "Incorrect number of query"<< endl;
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ProjectsMenu::handleDeleting(Project* project)
{
	project->setStatus(DELETED);
}

ProjectsMenu::~ProjectsMenu()
{
}
