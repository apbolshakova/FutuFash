#pragma once
#include "Entities.h"

using namespace std;

string Designer::getVogue()
{
	return this->vogue;
}
void Designer::setVogue(string vogue)
{
	try
	{
		if (vogue.empty())
			throw exception();
		this->vogue = vogue;
	}
	catch (const exception&)
	{
		cout << "New vogue cannot be empty string." << endl;
	}

}





