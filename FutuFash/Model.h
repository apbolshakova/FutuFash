#pragma once
#include "Common.h"
#include "User.h"
class User;
class Model :
	public User
{
private:
	int height;
	int weight;
	std::string hairColor;
public:
	Model(int height = 0, int weight = 0, std::string hairColor = "") : height(height), weight(weight), hairColor(hairColor) {};
	int getHeight();
	int getWeight();
	std::string getHairColor();
	void setHeight(int height);
	void setWeight(int weight);
	void setHairColor(std::string hairColor);
	
};

