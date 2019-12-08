#pragma once
#include "Common.h"
#include "SearchHandler.h"

class Menu
{
protected:
	int getOperationCode(int min = 0, int max = 0, char exitBtnCode = 0x1B);
	virtual void printMenu() {};
	void handleWarning();
	void printSuccessMessage();
};
