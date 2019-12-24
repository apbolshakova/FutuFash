#pragma once
#include "UserMenu.h"

using namespace std;

UserMenu::UserMenu(map<int, User*> *users = nullptr, UserMenuMode mode = GLOBAL_CHANGING, Project* projectToEdit = nullptr)
{
	switch (mode)
	{
	case GLOBAL_CHANGING:
	{
		if (!users) throw exception("No users structure found.");
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
				this->handleSearch(mode);
			}
			default: break;
			}
		} while (opCode != exitBtnCode);
		break;
	}
	case PROJECT_CHANGING:
	{
		this->users = users;
		this->projectToEdit = projectToEdit;
		cout << "You need to search required models. Press any button to start searching." << endl;
		_getch();
		this->handleSearch(mode);
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
	try
	{
		designer->setId(key);
	cout << "Enter the data:\n" <<
		"Name: ";
	string name;
	getline(cin, name);
	designer->setName(name);
	
	cout << "Work experience (in years): ";
	int exp;
	string line;
	getline(cin, line);
	if (line.find_first_not_of("0123456789") == string::npos)
		exp = atoi(line.c_str());
		else throw exception("Experience must be a positive number.");
	designer->setExp(exp);

	cout << "Vogue: ";
	string vogue;
	getline(cin, vogue);
	designer->setVogue(vogue);

	this->users->insert(pair<int, Designer*>(designer->getId(), designer));
    }
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Creation is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
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
	try
	{
		model->setId(key);
		cout << "Enter the data:\n" <<
			"Name: ";
		string name;
		getline(cin, name);
		model->setName(name);

		cout << "Work experience (in years): ";
		int exp;
		string line;
		getline(cin, line);
		if (line.find_first_not_of("0123456789") == string::npos)
			exp = atoi(line.c_str());
		else throw exception("Experience must be a positive number.");
		model->setExp(exp);

		cout << "Height: ";
		int height;
		getline(cin, line);
		if (line.find_first_not_of("0123456789") == string::npos)
			height = atoi(line.c_str());
		else throw exception("Height must be a positive number.");
		model->setHeight(height);

		cout << "Weight: ";
		int weight;
		getline(cin, line);
		if (line.find_first_not_of("0123456789") == string::npos)
			weight = atoi(line.c_str());
		else throw exception("Weight must be a positive number.");
		model->setWeight(weight);

		cout << "Hair color: ";
		string hairColor;
		getline(cin, hairColor);
		model->setHairColor(hairColor);

		this->users->insert(pair<int, Model*>(model->getId(), model));
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Creation is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
}
void UserMenu::printAllUsers()
{
	system("cls");
	if (users->empty())
		cout << "No users in the system." << endl;
	else
	{
		bool empty = true;
		for (auto const& el : *(this->users))
		{
			if (!el.second->isDeleted())
			{
				empty = false;
				cout << el.first << ". " << el.second->getName() << " ";
				if (dynamic_cast<Model*>(el.second))
					cout << " - model" << endl;
				else cout << " - designer" << endl;
			}
		}
		if (empty)
		{
			cout << "No users in the system." << endl;
		}
	}
	cout << "Press any button to return." << std::endl;
	_getch();
}
void UserMenu::handleSearch(UserMenuMode mode)
{
	SearchEntityType type;
	if (mode == GLOBAL_CHANGING)
	{
		type = USR;
		SearchHandler Search(type, this->users);
		vector<User*> data;
		Search.getResult(data);
		cout << endl;
		if (!data.empty())
		{
			Search.printResult(data);
			cout << endl;
			cout << "Do you want to work with particular profile? 1 - yes, 2 - no" << endl;
			int t;
			bool boolean = true;
			while (boolean)
			{
				cin >> t;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (t == 1 || t == 2) boolean = false;
				else cout << "Incorrect input. Please try again." << endl;
			}
			if (t == 1) this->handleProfile(data, mode);
		}
		else
		{
			cout << "No matches, please verify your query." << endl;
			cout << "Press any button to return.";
			_getch();
		}
	}
	else
	{
		type = MDL;
		SearchHandler Search(type, this->users);
		vector<Model*> data;
		Search.getResult(data);
		cout << endl;
		if (!data.empty())
		{
			Search.printResult(data);
			vector<User*> dataAsUsers;
			for (auto const& el : data)
			{
				dataAsUsers.push_back(el);
			}
			cout << endl;
			cout << "Do you want to work with particular profile? 1 - yes, 2 - no" << endl;
			int t;
			bool boolean = true;
			while (boolean)
			{
				cin >> t;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (t == 1 || t == 2) boolean = false;
				else cout << "Incorrect input. Please try again." << endl;
			}
			if (t == 1) this->handleProfile(dataAsUsers, mode);
		}
		else
		{
			cout << "No matches, please verify your query." << endl;
			cout << "Press any button to return.";
			_getch();
		}
	}
}
void UserMenu::handleProfile(vector<User*> data, UserMenuMode mode)
{
	cout << endl;
	int number = getNumToShow(data);
	Model* model = dynamic_cast<Model*>(data[number]);
	Designer* designer = dynamic_cast<Designer*>(data[number]);
	if (model)
	{
		printProfile(model);
		if (mode == GLOBAL_CHANGING)
		{
			cout << "Do you want to change the user's data? 1 - yes, 2 - no" << endl;
			int t;
			bool boolean = true;
			while (boolean)
			{
				cin >> t;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (t == 1 || t == 2) boolean = false;
				else cout << "Incorrect input. Please try again." << endl;
			}
			if (t == 1)
			{
				cout << endl;
				cout << "Choose the number" << endl;
				cout << "1- Change data, 2- Delete this user" << endl;
				int k;
				boolean = true;
				while (boolean)
				{
					cin >> k;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (k == 1 || k == 2) boolean = false;
					else cout << "Incorrect input. Please try again." << endl;
				}
				if (k == 1) handleGlobalChanging(model);
				else if (k == 2) handleGlobalDeleting(data[number]);
			}
		}
		else
		{
			if (model->getProjects()->count(this->projectToEdit->getId()) == 0) 
			{
				cout << "This model will be added to the project." << endl;
				try 
				{
					this->handleWarning();
				}
				catch (const std::exception& e)
				{
					cout << e.what() << endl;
					cout << "Press any button to return." << endl;
					_getch();
					return;
				}
				handleProjectAdding(model);
				cout << "Press any button to return." << endl;
				_getch();
			}
			else
			{
				cout << "This model will be deleted from the project." << endl;
				try
				{
					this->handleWarning();
				}
				catch (const std::exception& e)
				{
					cout << e.what() << endl;
					cout << "Press any button to return." << endl;
					_getch();
					return;
				}
				handleProjectDeleting(model);
				cout << "Press any button to return." << endl;
				_getch();
			}
		}
	}
	else
	{
		printProfile(designer);
		cout << "Do you want to change the user's data? 1 - yes, 2 - no" << endl;
		int t;
		bool boolean = true;
		while (boolean)
		{
			cin >> t;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (t == 1 || t == 2) boolean = false;
			else cout << "Incorrect input. Please try again." << endl;
		}
		if (t == 1)
		{
			cout << endl;
			cout << "Choose the number" << endl;
			cout << "1- Change data, 2- Delete this user" << endl;
			int k;
			boolean = true;
			while (boolean)
			{
				cin >> k;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (k == 1 || k == 2) boolean = false;
				else cout << "Incorrect input. Please try again." << endl;
			}
			if (k == 1) handleGlobalChanging(designer);
			else if (k == 2) handleGlobalDeleting(data[number]);
		}
	}
}
int UserMenu::getNumToShow(vector<User*> data)
{
	cout << "Which user to show? 1- first, " << data.size() << "- last" << endl;
	int opCode;
	bool t = true;
	while (t)
	{
		cin >> opCode;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (opCode >= 1 && opCode <= data.size()) t = false;
		else cout << "Incorrect input. Please try again." << endl;
	}
	return opCode - 1;
}
void UserMenu::printProfile(Designer* designer)
{
	system("cls");
	cout << "Name: "<< designer->getName() << endl;
	cout << "Work experience: "<<designer->getExp() <<" year(s)"<< endl;
	
	map<int, Project*>* projects = designer->getProjects();
	if (projects->size() != 0)
	{
		cout << "Taking/took part in the following projects:" << endl;
		map<int, Project*>::iterator iter = projects->begin();
		for (int i = 0; iter != projects->end(); i++, iter++)
		{
			cout << i+1 <<". " << iter->second->getName() << endl;
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

	map<int, Project*>* projects = model->getProjects(); 
	if (projects->size() != 0)
	{
		cout << "Taking/took part in the following projects:" << endl;
		map<int, Project*>::iterator iter = projects->begin();
		for (int i = 0; iter != projects->end(); i++, iter++)
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
template <class X> void UserMenu::changeName(X* user)
{
	cout << "Enter new name: ";
	try
	{
		string name;
		getline(cin, name);
		user->setName(name);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Changing is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
}
template <class X> void UserMenu::changeExperience(X* user)
{
	cout << "Enter new work experience (in years): ";
	try
	{
		int exp;
		string line;
		getline(cin, line);
		if (line.find_first_not_of("0123456789") == string::npos)
			exp = atoi(line.c_str());
		else throw exception("Experience must be a positive number.");
		user->setExp(exp);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Changing is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
}
void UserMenu::changeVogue(Designer* designer)
{
	cout << "Enter new vogue: ";
	try
	{
		string vogue;
		getline(cin, vogue);
		designer->setVogue(vogue);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Changing is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
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
} 
void UserMenu::changeHeight(Model* model)
{
	cout << "Enter new height: ";
	try
	{
		int height;
		string line;
		getline(cin, line);
		if (line.find_first_not_of("0123456789") == string::npos)
			height = atoi(line.c_str());
		else throw exception("Height must be a positive number.");
		model->setHeight(height);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Changing is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
}
void UserMenu::changeWeight(Model* model)
{
	cout << "Enter new weight: ";
	try
	{
		int weight;
		string line;
		getline(cin, line);
		if (line.find_first_not_of("0123456789") == string::npos)
			weight = atoi(line.c_str());
		else throw exception("Weight must be a positive number.");
		model->setWeight(weight);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Changing is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
}
void UserMenu::changeHairColor(Model* model)
{
	cout << "Enter new hair color: ";
	try
	{
		string hairColor;
		getline(cin, hairColor);
		model->setHairColor(hairColor);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		cout << "Changing is aborted. Press any button to return." << endl;
		_getch();
		return;
	}
}
 void UserMenu::handleGlobalDeleting(User* user)
{ 
	user->markToDelete();
	if (dynamic_cast<Designer*>(user) != nullptr)
	{
		for (auto const& el : *(user->getProjects()))
			el.second->setStatus(DELETED);
	}
	else
	{
		for (auto const& el : *(user->getProjects()))
		    el.second->removeModel(dynamic_cast<Model*>(user));
	}
}
void UserMenu::handleProjectAdding(Model* model)
{
	model->addProject(this->projectToEdit);
	this->projectToEdit->addModel(model);
	this->printSuccessMessage();
}
void UserMenu::handleProjectDeleting(Model* model)
{
	model->removeProject(this->projectToEdit);
	this->projectToEdit->removeModel(model);
	this->printSuccessMessage();
}

UserMenu::~UserMenu()
{
}

