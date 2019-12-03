#pragma once
#include "Common.h"

class Menu
{
protected:
	int getOperationCode(int min, int max, char exitBtnCode);
	virtual void printMenu() {};
	void handleWarning();
	void printSuccessMessage();
};

