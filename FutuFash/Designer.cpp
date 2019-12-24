#pragma once
#include "Entities.h"

using namespace std;

string Designer::getVogue()
{
	return this->vogue;
}
void Designer::setVogue(string vogue)
{
		if (vogue.empty())
			throw exception("Vogue cannot be empty string.");
		this->vogue = vogue;
}

Designer::~Designer()
{
	free(this->getProjects());
}



