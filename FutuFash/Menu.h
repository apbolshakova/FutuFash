#pragma once
#include "Common.h"


class Menu
{
protected:
	int getOperationCode(int min = 0, int max = 0);
	virtual void printMenu() {};
	void handleWarning();
	void printSuccessMessage();
};

