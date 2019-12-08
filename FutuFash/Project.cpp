#pragma once
#include "Project.h"

using namespace std;

string Project::getName(void)
{
	return this->name;
}
int Project::getId(void)
{
	return this->id;
}
string Project::getDate(void)
{
	return this->date;
}
string Project::getLocation(void)
{
	return this->location;
}
Designer* Project::getDesigner(void)
{
	return this->designer;
}
map<int, Model*> Project::getModels(void)
{
	return this->models;
}
enum ProjectStatus  Project::getStatus(void)
{
	return this->status;
}
void Project::setDate(string date)
{
	Project::date = date;
}
void Project::setLocation(string location)
{
	Project::location = location;
}
void Project::addModel(Model* model)
{
	Project::models.insert(pair< int, Model*>(model->getId(), model));
}
void Project::removeModel(Model* model)
{
	Project::models.erase(model->getId());
}
void Project::setStatus(enum ProjectStatus status)
{
	Project::status = status;
}
void Project::setDesigner(Designer* designer)
{
	Project::designer = designer;
}
