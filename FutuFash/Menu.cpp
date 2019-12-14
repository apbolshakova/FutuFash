#pragma once
#include "Menu.h"

int Menu::getOperationCode(int min, int max, char exitBtnCode)
{
	if (!min || !max) throw new std::exception("Invalid operations range.");
	int opCode = 0;
	do 
	{
		opCode = _getch();

	} while ((min > opCode - '0' || max < opCode - '0') && opCode != exitBtnCode);
	if (opCode != exitBtnCode) opCode -= '0';
	return opCode;
}


void Menu::handleWarning()
{
	const int confCode = 0x0D;
	const int abortCode = 0x1B;
	char ch = 0;
	std::cout << "Are you sure? Press Enter to confirm or Esc to abort." << std::endl;
	do {
		ch = _getch();
	} while (ch != confCode && ch != abortCode);
	if (ch == abortCode) throw new std::exception("Operation was aborted.");
}


void Menu::printSuccessMessage()
{
	std::cout << "Success." << std::endl;
}
