#include "UserMenu.h"



UserMenu::UserMenu(map<int, User*> *users = nullptr, UserMenuMode mode, Project* projectToEdit)
{
	//system("cls");
	switch (mode)
		case GLOBAL_CHANGING:
	{
		if (!users) throw new exception("No users structure found.");

		//this->users = users;
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
			case SEARCH: this->handleSearch(); break;
			default: break;
			}
		} while (opCode != exitBtnCode);

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
		case DESIGNER:	this->addNew(Designer* designer); break;
		case MODEL: this->addNew(Model* model); break;
		default: break;

	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

UserMenu::~UserMenu()
{
}

