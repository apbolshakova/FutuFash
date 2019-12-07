#include "Designer.h"
using namespace std;
string Designer::GetVogue()
{
	return this->vogue;
}
void Designer::SetVogue(string vogue)
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





