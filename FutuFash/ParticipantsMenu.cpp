#include "ParticipantsMenu.h"
using namespace std;


ParticipantsMenu::ParticipantsMenu(map<int, User*> *users, Project* project)
{
	this->users = users;
	this->project = project;
	const char exitBtnCode = 0x1B;
	char opCode = 0;
	do
	{
		system("cls");
		this->printMenu();
		enum OpCodes { PRINTING = 1, CHANGING };

		std::cout << "������� ����� ������������� ��� ��������" << endl;
		opCode = this->getOperationCode(PRINTING, CHANGING, exitBtnCode);
		switch (opCode)
		{
		case PRINTING: this->printAllParticipants(); break;
		case CHANGING: this->changeParticipants(); break;
		default:
		{
			cout << "������ ������� �� ����������";
			break;
		}
		}

	} while (opCode != exitBtnCode);
}
void ParticipantsMenu::printMenu()
{
	cout << "	1- ������� ���� ���������� �������" << endl;
	cout << "	2- �������� ���������� �������" << endl;
	cout << "Esc- �����" << endl;

}
void ParticipantsMenu::printAllParticipants()
{
	map<int, Model*> mapmod = this->project->getModels();
	map <int, Model*> ::iterator it = mapmod.begin();
	for (int i = 0; it != mapmod.end(); i++, it++)
		cout << i++ << ") " << it->second->getName() << endl;
}
void ParticipantsMenu::changeParticipants()
{

}

ParticipantsMenu::~ParticipantsMenu()
{
}
