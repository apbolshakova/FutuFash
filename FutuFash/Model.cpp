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
		if (height <= 0)
			throw exception("Height cannot be non-positive.");
		this->height = height;
}
void Model::setWeight(int weight)
{
		if (weight <= 0)
			throw exception("Weight cannot be non-positive.");
		this->weight = weight;
}
void Model::setHairColor(string hairColor)
{
		if (hairColor.empty())
			throw exception("Hair color cannot be empty string.");
		this->hairColor = hairColor;
}

Model::~Model()
{
	free(this->getProjects());
}



