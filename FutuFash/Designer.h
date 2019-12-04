#pragma once
#include "Common.h"
using namespace std;
class Designer :
	public User
{
private:
	string vogue;

public:
	Designer(string vogue = "") : vogue(vogue) {};
	string GetVogue();
	void SetVogue(string vogue);
	~Designer();
};

