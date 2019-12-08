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
				//TODO
				this->handleSearch();
			//	this->getNumToShow();
					//if это модель вызываем printProfile(model) иначе printProfile(designer)
				//enum operCodes { CHANGE = 1, DELETE };
			//	char operCode = 0;
				//cout << "Press 1 to change the data       Press 2 to delete the user" << endl;
				//operCode = this->getOperationCode(CHANGE, DELETE, exitBtnCode);
			//	switch (operCode)
			//	{
					//case CHANGE: if это модель вызываем handleGlobalChanging(model) else handleGlobalChanging(designer)
					//case DELETE: if это модель вызываем handleGlobalDeleting(model) else handleGlobalDeleting(designer)
			//	}
			//	break;
			}
			default: break;
			}
		} while (opCode != exitBtnCode);
		break;
	}
	case PROJECT_CHANGING:
	{
		//TODO
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
			Designer* newUser;
			
		addNew(newUser);
		break;
		}
		case MODEL:
		{
			
			Model* newUser;
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
	map<int, User*> ::iterator iter = this->users->end();//check
	int key = iter->first + 1;//check
	designer->setId(key);//check
	cout << "Enter your data:\n" <<
		"Your name: ";
	string name;
	cin >> name;
	designer->setName(name);
	cout << "Your work experience (in years): ";
	int exp;
	cin >> exp;
	designer->setExp(exp);
	cout << "Your vogue: ";
	string vogue;
	cin >> vogue;
	designer->SetVogue(vogue);
	this->users->insert(pair<int, Designer*>(designer->getId(),designer));
}
void UserMenu::addNew(Model* model)
{
	system("cls");
	map<int, User*>::iterator iter = this->users->end();//check
	int key = iter->first + 1;//check
	model->setId(key); //check
	cout << "Enter your data:\n" <<
		"Your name: ";
	string name;
	cin >> name;
	model->setName(name);
	cout << "Your work experience (in years): ";
	int exp;
	cin >> exp;
	model->setExp(exp);
	cout << "Your height: ";
	int height;
	cin >> height;
	model->setHeight(height);
	cout << "Your weight: ";
	int weight;
	cin >> weight;
	model->setWeight(weight);
	cout << "Your hair color: ";
	string hairColor;
	cin >> hairColor;
	model->setHairColor(hairColor);
	this->users->insert(pair<int, Model*>(model->getId(), model));
}
void UserMenu::printAllUsers()
{
	map<int, User*> ::iterator iter = this->users->begin();
	for (int i = 0; iter != this->users->end(); i++, iter++)
	{
		cout << i++ << ". " << iter->second->getName() << endl;
	}
}
void UserMenu::handleSearch()
{
	//TODO
	//SearchEntityType type = USER;
	//SearchHandler Search(type);
	//vector<User*> data = Search.getResult();
	//Search.printResult();
	//cout << endl;
	//cout << "Type true to go to a certain profile" << endl;
	//bool t = false;
	//cin >> t;
	//if (t)
		//this->handleProfile(data);
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
		cout << "Press 1 to change the data       Press 2 to delete the user" << endl;
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
		cout << "Press 1 to change the data       Press 2 to delete the user" << endl;
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
	cout << "Work experience: "<<designer->GetExp() <<" year(s)"<< endl;
	
	map<int, Project*>* projects = designer->GetProjects();
	if (projects != nullptr)
	{
		cout << "Taking/took part in the following projects:" << endl;
		map<int, Project*>::iterator iter = projects->begin();
		for (int i = 0; iter != projects->end(); i++, iter++)
		{
			cout << i++<<". " << iter->second->getName() << endl;
		}
	}
	cout <<"Vogue: "<< designer->GetVogue();
}
void UserMenu::printProfile(Model* model)
{
	system("cls");
	cout << "Name: "<< model->getName() << endl;
	cout << "Work experience: "<<model->GetExp() << " year(s)" << endl;

	map<int, Project*>* projects = model->GetProjects();
	if (projects != nullptr)
	{
		cout << "Taking/took part in the following projects:" << endl;
		map<int, Project*>::iterator iter = projects->begin();
		for (int i = 0; iter != projects->end(); i++, iter++)
		{
			cout << i++<<". "<<iter->second->getName() << endl;
		}
	}
	cout <<"Height: "<< model->getHeight()<<endl;
	cout << "Weight: "<<model->getWeight()<<endl;
	cout << "Hair color: "<<model->getHairColor() << endl;
}
void UserMenu::handleGlobalChanging(Designer* designer)
{
	
			cout << "Enter new data:\n" <<
				"Name: ";
			string name;
			cin >> name;
			designer->setName(name);
			cout << "Work experience (in years): ";
			int exp;
			cin >> exp;
			designer->setExp(exp);
			cout << "Vogue: ";
			string vogue;
			cin >> vogue;
			designer->SetVogue(vogue);
			
}
void UserMenu::handleGlobalChanging(Model* model)
{
	/*cout << endl;
	cout << "Do you want to change parameters?" << 
		"1 - yes, 2 - no" << endl;
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		enum OpCodes { YES = 1, NO };
		opCode = this->getOperationCode(YES, NO, exitBtnCode);
		switch (opCode)
		{
		case YES:*/
		//подумать о возможном изменении не всех полей, а каких-то конкретных
			cout << "Enter new data:\n" <<
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
			model->setHairColor(hairColor);
			/*break;
		}
		case NO: 
			break;
		default:
			break;
		}
	} while (opCode != exitBtnCode);*/
} 
void UserMenu::handleGlobalDeleting(User* user)
{
	//получается само удаление будет при сохранении данных? 
	user->markToDelete();//вопрос: или тоже разделить на два метода отдельно для модели и дизайнера
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

