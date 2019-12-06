#pragma once
#include "Common.h"
#include "User.h"
using namespace std;
class Model :
	public User
{
private:
	int height;
	int weight;
	string hairColor;
public:
	Model(int height = 0, int weight = 0, string hairColor = "") : height(height), weight(weight), hairColor(hairColor) {};
	int getHeight();
	int getWeight();
	string getHairColor();
	void setHeight(int height);
	void setWeight(int weight);
	void setHairColor(string hairColor);
	
};

