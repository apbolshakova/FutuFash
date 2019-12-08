#pragma once
#include "Common.h"

class User;

class Designer :
	public User
{
private:
	std::string vogue;

public:
	Designer(std::string vogue = "") : vogue(vogue) {};
	std::string GetVogue();
	void SetVogue(std::string vogue);

};