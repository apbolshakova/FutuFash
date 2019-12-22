#pragma once
#include "UserMenu.h"

using namespace std;

UserMenu::UserMenu(map<int, User*> *users = nullptr, UserMenuMode mode = GLOBAL_CHANGING, Project* projectToEdit = nullptr)
{
	//system("cls");
	switch (mode)
	{
	case GLOBAL_CHANGING:
	{
		if (!users) throw new exception("No users structure found.");

		this->users = users;
		const char exitBtnCode = 0x1B;
		char opCode = 0;

		do
		{
			system("cls");
			this->printMenu();
			enum OpCodes { ADDING = 1, PRINT_ALL, SEARCH };

			cout << "Press button of required operation." << endl;
			opCode = this->getOperationCode(ADDING, SEARCH, exitBtnCode);
			switch (opCode)
			{
			case ADDING: this->handleAdding(); break;
			case PRINT_ALL: this->printAllUsers(); break;
			case SEARCH: 
			{
				this->handleSearch();
			}
			default: break;
			}
		} while (opCode != exitBtnCode);
		break;
	}
	case PROJECT_CHANGING:
	{
		this->users = users;
		this->handleSearch();
	}
	}
}
void UserMenu::printMenu()
{
	system("cls");
	cout <<
		"1  - Add new user to the system\n" <<
		"2  - Display all users in the system\n" <<
		"3  - Find a user by a certain parameter\n" <<
		"Esc - Exit" << endl;

}
void UserMenu::handleAdding()
{
	system("cls");
	try
	{
		cout <<
			" 1  - Create a designer\n" <<
			" 2  - Create a model\n" <<
			"Esc - Exit" << endl;
		const char exitBtnCode = 0x1B;
		enum OpCodes { DESIGNER = 1, MODEL };
		cout << "Press button of required operation." << endl;
		char opc = 0;
		opc = this->getOperationCode(DESIGNER, MODEL, exitBtnCode);
		
		switch (opc) 
		{
		case DESIGNER:	
		{
			Designer* newUser = new Designer();
			
		addNew(newUser);
		break;
		}
		case MODEL:
		{
			
			Model* newUser = new Model();
		addNew(newUser);
		break;
		}
		default: break;
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}
void UserMenu::addNew(Designer* designer)
{
	system("cls");
	int key = 1;
	if (this->users->size() != 0)
	{
		map<int, User*> ::iterator iter = --this->users->end();
		key = iter->first + 1;
	}
	designer->setId(key);
	cout << "Enter the data:\n" <<
		"Name: ";
	string name;
	cin >> name;
	designer->setName(name);
	int exp;
	cout << "Work experience (in years): ";
	bool t = true;
	while (t)
	{
		
		cin >> exp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	designer->setExp(exp);
	cout << "Vogue: ";
	string vogue;
	cin >> vogue;
	designer->setVogue(vogue);
	this->users->insert(pair<int, Designer*>(designer->getId(),designer));
}
void UserMenu::addNew(Model* model)
{
	system("cls");
	int key = 1;
	if (this->users->size() != 0)
	{
		map<int, User*> ::iterator iter = --this->users->end();
		key = iter->first + 1;
	}
	model->setId(key);
	cout << "Enter the data:\n" <<
		"Name: ";
	string name;
	cin >> name;
	model->setName(name);
	cout << "Work experience (in years): ";
	int exp;
	bool t = true;
	while (t)
	{

		cin >> exp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	model->setExp(exp);
	cout << "Height: ";
	int height;
	t = true;
	while (t)
	{

		cin >> height;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	model->setHeight(height);
	cout << "Weight: ";
	int weight;
	t = true;
	while (t)
	{
		cin >> weight;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	model->setWeight(weight);
	cout << "Hair color: ";
	string hairColor;
	cin >> hairColor;
	model->setHairColor(hairColor);
	this->users->insert(pair<int, Model*>(model->getId(), model));
}
void UserMenu::printAllUsers()
{
	system("cls");
	if (users->empty())
		cout << "No users in the system." << endl;
	else
	for (auto const& el : *(this->users))
	{
	//	if (el.second->toDelete == false)
		std::cout << el.first << ". " << el.second->getName() << std::endl;
	}
	cout << "Press any button to return." << std::endl;
	_getch();
}
void UserMenu::handleSearch()
{
	SearchEntityType type = USR;
	SearchHandler Search(type, this->users);
	vector<User*> data;
	Search.getResult(data);
	Search.printResult(data);
	cout << endl;
	if (!data.empty())
	{
		cout << "Do you want to work with particular profile? 1- yes, 0- no" << endl;
		bool t;
		cin >> t;
		if (t) this->handleProfile(data);
	}
	else
	{
		cout << "Press any button to return.";
		_getch();
	}
}
void UserMenu::handleProfile(vector<User*> data)
{
	int number = getNumToShow(data);
	Model* model = dynamic_cast<Model*>(data[number]);
	Designer* designer = dynamic_cast<Designer*>(data[number]);
	if (model)
	{
		printProfile(model);
		
		enum operCodes { CHANGE = 1, DELETE };
		char operCode = 0;
		cout << "Press 1 to change the data       Press 2 to delete the user       Press Esc to exit" << endl;
		operCode = this->getOperationCode(CHANGE, DELETE);
		switch (operCode)
		{
		case CHANGE: handleGlobalChanging(model); break;
		case DELETE: handleGlobalDeleting(data[number]); break;
		default: break;
		}
	}
	else
	{
		printProfile(designer);
		enum operCodes { CHANGE = 1, DELETE };
		char operCode = 0;
		cout << "Press 1 to change the data       Press 2 to delete the user       Press Esc to exit" << endl;
		cout << endl;
		operCode = this->getOperationCode(CHANGE, DELETE);
		switch (operCode)
		{
		case CHANGE: handleGlobalChanging(designer); break;
		case DELETE: handleGlobalDeleting(data[number]); break;
		default: break;
		}
	}
}
int UserMenu::getNumToShow(vector<User*> data)
{
	cout << "Enter profile ordinal number from the list: ";
	int opCode = 0;
	opCode = this->getOperationCode(1, data.size());
	return opCode - 1;
}
void UserMenu::printProfile(Designer* designer)
{
	system("cls");
	cout << "Name: "<< designer->getName() << endl;
	cout << "Work experience: "<<designer->getExp() <<" year(s)"<< endl;
	
	map<int, Project*>* projects = designer->getProjects(); //на каком этапе у нас будет вызываться метод addProject?
	if (projects != nullptr)
	{
		cout << "Taking/took part in the following projects:" << endl;
		map<int, Project*>::iterator iter = projects->begin();
		for (int i = 0; iter != projects->end(); i++, iter++)
		{
			cout << i+1 <<". " << iter->second->getName() << endl; //check
		}
	}
	cout <<"Vogue: "<< designer->getVogue()<<endl;
	cout << endl;
}
void UserMenu::printProfile(Model* model)
{
	system("cls");
	cout << "Name: "<< model->getName() << endl;
	cout << "Work experience: "<<model->getExp() << " year(s)" << endl;

	map<int, Project*>* projects = model->getProjects(); //на каком этапе у нас будет вызываться метод addProject?
	if (projects != nullptr)
	{
		cout << "Taking/took part in the following projects:" << endl;
		map<int, Project*>::iterator iter = projects->begin();
		for (int i = 0; iter != projects->end(); i++, iter++) //check
		{
			cout << i+1<<". "<<iter->second->getName() << endl;
		}
	}
	cout <<"Height: "<< model->getHeight()<<endl;
	cout << "Weight: "<<model->getWeight()<<endl;
	cout << "Hair color: "<<model->getHairColor() << endl;
	cout << endl;
}
void UserMenu::handleGlobalChanging(Designer* designer)
{
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		cout << "Select a number" << endl;
		enum OpCodes { NAME = 1, EXPERIENCE, VOGUE };
		cout << "   1- change user name" << endl;
		cout << "   2- change experience" << endl;
		cout << "   3- change vogue" << endl;
		cout << "Esc - return to user menu" << endl;
		opCode = this->getOperationCode(NAME, VOGUE, exitBtnCode);
		switch (opCode)
		{
		case NAME: this->changeName(designer); break;
		case EXPERIENCE: this->changeExperience(designer); break;
		case VOGUE: this->changeVogue(designer); break;
		default: cout << "Incorrect number of query" << endl; break;
		}
	} while (opCode != exitBtnCode);
}
template <class X> void UserMenu::changeName(X* desormod)
{
	cout << "Enter new name: ";
	string name;
	cin >> name;
	desormod->setName(name);
}
template <class X> void UserMenu::changeExperience(X* desormod)
{
	cout << "Enter new work experience (in years): ";
	int exp;
	bool t = true;
	while (t)
	{

		cin >> exp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	desormod->setExp(exp);
}
void UserMenu::changeVogue(Designer* designer)
{
	cout << "Enter new vogue: ";
	string vogue;
	cin >> vogue;
	designer->setVogue(vogue);
}
void UserMenu::handleGlobalChanging(Model* model)
{
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		cout << "Select a number" << endl;
		enum OpCodes { NAME = 1, EXPERIENCE, HEIGHT, WEIGHT, HAIRCOLOR };
		cout << "   1- change user name" << endl;
		cout << "   2- change experience" << endl;
		cout << "   3- change height" << endl;
		cout << "   4- change weight" << endl;
		cout << "   5- change hair color" << endl;
		cout << "Esc - return to user menu" << endl;
		opCode = this->getOperationCode(NAME, HAIRCOLOR, exitBtnCode);
		switch (opCode)
		{
		case NAME: this->changeName(model); break;
		case EXPERIENCE: this->changeExperience(model); break;
		case HEIGHT: this->changeHeight(model); break;
		case WEIGHT: this->changeWeight(model); break;
		case HAIRCOLOR: this->changeHairColor(model); break;
		default: cout << "Incorrect number of query" << endl; break;
		}
	} while (opCode != exitBtnCode);
		/*	cout << "Enter new data:\n" <<
				"Name: ";
			string name;
			cin >> name;
			model->setName(name);
			cout << "Work experience (in years): ";
			int exp;
			cin >> exp;
			model->setExp(exp);
			cout << "Height: ";
			int height;
			cin >> height;
			model->setHeight(height);
			cout << "Weight: ";
			int weight;
			cin >> weight;
			model->setWeight(weight);
			cout << "Hair color: ";
			string hairColor;
			cin >> hairColor;
			model->setHairColor(hairColor);*/
			
} 
void UserMenu::changeHeight(Model* model)
{
	cout << "Enter new height: ";
	int height;
	bool t = true;
	while (t)
	{

		cin >> height;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	model->setHeight(height);
}
void UserMenu::changeWeight(Model* model)
{
	cout << "Enter new weight: ";
	int weight;
	bool t = true;
	while (t)
	{

		cin >> weight;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Incorrect input. Please try again." << endl;
		}
		else t = false;
	}
	model->setWeight(weight);
}
void UserMenu::changeHairColor(Model* model)
{
	cout << "Enter new hair color: ";
    string hairColor;
		cin >> hairColor;
	model->setHairColor(hairColor);
}
template <class X> void UserMenu::handleGlobalDeleting(X* desormod)
{ 
	desormod->markToDelete();
}
void UserMenu::handleProjectAdding(User* user)
{
  //TODO разобраться с доступом к projects и мэпе моделей проекта
}
void UserMenu::handleProjectDeleting(User* user)
{
	//TODO
}

UserMenu::~UserMenu()
{
}

