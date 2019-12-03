#include "Menu.h"


int Menu::getOperationCode(int min = 0, int max = 0)
{
	if (!min || !max) throw new std::exception("Invalid operations range.");
	int opCode = 0;
	do 
	{
		std::cout << "Enter number of required operation: ";
		std::cin >> opCode;

	} while (min > opCode || max < opCode);
	return opCode;
}


void Menu::handleWarning()
{
	const int confCode = 0x0D;
	const int abortCode = 0x1B;
	char ch = 0;
	std::cout << "Are you sure? Press Enter to confirm or Esc to abort." << std::endl;
	do {
		std::cin >> ch;
	} while (ch != confCode && ch != abortCode);
	if (ch == abortCode) throw new std::exception("Operation was aborted.");
}


void Menu::printSuccessMessage()
{
	std::cout << "Success." << std::endl;
}