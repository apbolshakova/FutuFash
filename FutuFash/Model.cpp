#pragma once
#include "Entities.h"

using namespace std;

int Model::getHeight()
{
	return this->height;
}
int Model::getWeight()
{
	return this->weight;
}
string Model::getHairColor()
{
	return this->hairColor;
}
void Model::setHeight(int height)
{
	try
	{
		if (height <= 0)
			throw exception();
		this->height = height;
	}
	catch (const exception&)
	{
		cout << "New height cannot be non-positive." << endl;
	}
}
void Model::setWeight(int weight)
{
	try
	{
		if (weight <= 0)
			throw exception();
		this->weight = weight;
	}
	catch (const exception&)
	{
		cout << "New weight cannot be non-positive." << endl;
	}
}
void Model::setHairColor(string hairColor)
{
	try
	{
		if (hairColor.empty())
			throw exception();
		this->hairColor = hairColor;
	}
	catch (const exception&)
	{
		cout << "New hair color cannot be empty string." << endl;
	}
}





