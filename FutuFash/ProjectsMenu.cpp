#pragma once
#include "ProjectsMenu.h"

using namespace std;

ProjectsMenu::ProjectsMenu(map<int, User*> *users, map<int, Project*> *projects)
{
	this->users = users;
	this->projects = projects;
	if (!users) throw exception("No users structure is found.");
	if (!projects) throw exception("No project structure is found.");
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
bool t = false;
for (auto const& el : *(this->users))
	if (dynamic_cast<Designer*>(el.second))
	{
		t = true;
	}
if (t)
{
	
	try
	{
		addNew();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}
else
{
	cout << "You need to add at least one designer to the base at first" << endl;
	cout << "Press any button to return" << endl;
	_getch();
}
}
void ProjectsMenu::printAllProjects()
{
	system("cls");
	if (projects->size() != 0)
	{
		bool empty = true;
		for (auto const& el : *(this->projects))
		{
			if (el.second->getStatus() != DELETED)
			{
				empty = false;
				cout << el.first << "." << el.second->getName() << endl;
			}
		}
		if (empty)
			cout << "You need to add at least one project to the base at first" << endl;
		cout << "Press any button to return" << endl;
		_getch();
	}
	else {
		
		cout << "You need to add at least one project to the base at first" << endl;
		cout << "Press any button to return" << endl;
		_getch();
	}
}

void ProjectsMenu::addNew()
{
	Project* project = new Project();
	system ("cls");
	cout << "Enter the data" << endl;
	
	cout << "Project name: ";
	string name;
	getline(cin, name);
	project->setName(name);
	bool t= true;
	string date;
	while (t)
	{
		cout << "Date of show (e.g. 01.01.2020): ";
		getline(cin, date);
		if (date.length() != 10 || date[2] != '.' || date[5] != '.'  )
		{
			date = "";
			cout << "Incorrect input, please try again"<< endl;
		}
		else t = false;
	}
	project->setDate(date);
	cout << "Location: ";
	string location;
	getline(cin, location);
	project->setLocation(location);
	project->setStatus(INSEARCH);
	cout << "Next step is designer adding. Press any button to start searching" << endl;
	_getch();
	Designer* designer; 
	try
	{
		designer = getNewDesigner();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Project creation will be aborted. Press any button to return"<< endl;
		_getch();
		return;
	}
	project->setDesigner(designer);
	printSuccessMessage();
	_getch();
	int key = 1;
	if (this->projects->size() != 0)
	{
		map<int, Project*>::iterator it = --this->projects->end();
		key = it->first + 1;
	}
	project->setId(key);
	this->projects->insert(pair< int, Project*>(key, project));
	designer->addProject(project);
}
void ProjectsMenu::handleSearch()
{
	system("cls");
	if (projects->size() != 0)
	{
		SearchEntityType type = PRJ;
		SearchHandler Search(type, this->users, this->projects);
		vector<Project*> data;
		Search.getResult(data);
		Search.printResult(data);
		if (data.size() != 0)
		{
			string opCode;
			bool t = true;
			while (t)
			{
				cout << "Do you want to work with particular profile? 1- yes, 0- no" << endl;
				getline(cin, opCode);
				if (opCode == "1" || opCode == "0") t = false;
				else cout << "Incorrect input. Please try again." << endl;
			}
			
			if (opCode == "1") this->handleProfile(data); 
		}
		else
		{
			cout << "Please verify your guery. Press any button to continue." << endl;
			_getch();
		}
	}
	else {
		cout << "We can't make a searching in an empty base" << endl;
		cout << "Press any button to return" << endl;
		_getch();
	}
}

Designer* ProjectsMenu::getNewDesigner()
{
	SearchEntityType type = DSG;
    SearchHandler Search(type, this->users, this->projects);
	vector<Designer*> data;
    Search.getResult(data);
	Search.printResult(data);
	if (data.size() == 0)
	{
		throw std::exception("No designer that can be attached.");
	}
	if (data.size() == 1)
	{
		cout << "This designer will be attacted to new project. Press any button to continue"<< endl;
		_getch();
		return data[0];
	}
	else
	{
		cout << "Choose required number" << endl;
		int number = getNumToShow(data.size());
		return data[number];
    }
}
void ProjectsMenu::handleProfile(vector<Project*> data)
{
	int number = getNumToShow(data.size());
	printProfile(data[number]);
	
	string opCode;
	bool t = true;
	while (t)
	{
		cout << "Do you want to change this project? 1- yes, 0- no" << endl;
		getline(cin, opCode);
		if (opCode == "1" || opCode == "0") t = false;
		else cout << "Incorrect input. Please try again." << endl;
	}
	if (opCode == "1" )
	{
		string k;
		t = true;
		while (t)
		{
			cout << "Choose the number" << endl;
			cout << "1- Change models, 2- Change other positions, 3- Delete this project" << endl;
			getline(cin, k);
			if (k == "1" || k == "2" || k == "3" ) t = false;
			else cout << "Incorrect input. Please try again." << endl;
		}
		if (k == "1")
			handleParticipantsMenu(data[number],this->users);
		else if (k == "2") handleChanging(data[number]);
		else if (k == "3") handleDeleting(data[number]);

	}
}
int ProjectsMenu::getNumToShow(int size)
{
		int opCode;
		bool t = true;
		while (t)
		{
			cout << "Which one to show? 1- first, " << size << "- last" << endl;
			cin >> opCode;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (opCode >= 1 && opCode <= size) t = false;
			else cout << "Incorrect input. Please try again." << endl;
		}
		return opCode - 1;
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
	cout << "   Name of designer : " << project->getDesigner()->getName() << endl;
	int OpCodes=0;
	switch (OpCodes= project->getStatus())
	{
	case 0: cout << "   Project status : in search of models" << endl; break;
	case 1: cout << "   Project status : waiting for show" << endl; break;
	case 2: cout << "   Project status : the show is finished" << endl; break;
	case 3: cout << "   Project status : the project is deleted" << endl; break; 
	}
	cout << "   Number of models : " << project->getModels().size() << endl;
	cout << endl;
}

void ProjectsMenu::handleChanging(Project* project)
{
	const char exitBtnCode = 0x1B;
	char opCode = 0;
		system("cls");
		cout << "Select a number" << endl;
		enum OpCodes { NAME = 1, DATE, LOCATION, STATUS };
		cout << "   1- change project name" << endl;
		cout << "   2- change date of show" << endl;
		cout << "   3- change location" << endl;
		cout << "   4- change project status" << endl;
		cout << "Esc - return to projects menu" << endl;
		opCode = this->getOperationCode(NAME, STATUS, exitBtnCode);
		switch (opCode)
		{
		case NAME: this->changeName(project); printSuccessMessage(); break;
		case DATE: this->changeDate(project); printSuccessMessage(); break;
		case LOCATION: this->changeLocation(project); printSuccessMessage(); break;
		case STATUS: this->changeStatus(project); printSuccessMessage(); break;
		default: cout << "Incorrect number of query"<< endl; break; 
		}
		
}
void ProjectsMenu::changeName(Project* project)
{
	cout << "Enter new name: " << endl;
	string newname; getline(cin,newname);
	project->setName(newname);
	printSuccessMessage();
}
void ProjectsMenu::changeDate(Project* project)
{
	cout << "Enter new date: " << endl;
	string newdate; getline(cin, newdate);
	project->setDate(newdate);
	printSuccessMessage();
}
void ProjectsMenu::changeLocation(Project* project)
{
	cout << "Enter new location: " << endl;
	string newlocation; getline(cin, newlocation);
	project->setLocation(newlocation);
	printSuccessMessage();
}
void ProjectsMenu::changeStatus(Project* project)
{
	const char exitBtnCode = 0x1B;
	char opCode = 0;
		cout << "Select a number" << endl;
		enum OpCodes { IN = 1, FIL, FIN};
		cout << "   1- in search of models" << endl;
		cout << "   2- waiting for show" << endl;
		cout << "   3- the show is finished" << endl;
		opCode = this->getOperationCode(IN, FIN, exitBtnCode);
		switch (opCode)
		{
		case IN: project->setStatus(INSEARCH); printSuccessMessage(); break;
		case FIL: project->setStatus(FILLED); printSuccessMessage(); break;
		case FIN: project->setStatus(FINISHED); printSuccessMessage(); break;
		default:
		{
			cout << "Incorrect number of query"<< endl;
			break;
		}
		}

}
void ProjectsMenu::handleDeleting(Project* project)
{
	project->setStatus(DELETED);
	project->getDesigner()->removeProject(project);
	for (auto const& el : project->getModels())
		el.second->removeProject(project);
	printSuccessMessage();
	cout << "Press any button to return." << std::endl;
	_getch();
}

ProjectsMenu::~ProjectsMenu()
{
}
