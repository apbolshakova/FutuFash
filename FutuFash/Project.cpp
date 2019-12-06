#include "Project.h"
#include <string>


Project::Project()
{


}
Project::~Project()
{
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
void Project::addModel(Model* model, int mid)
{
	Project::models.insert(pair< int, Model*>(mid, model));
}
void Project::removeModel(Model* model, int mid)
{
	for (int i = 0; i < models.end; i++)
		if (mid == models[i].key_comp)
			Project::models.erase(pair< int, Model*>(mid, model));
}
void Project::setStatus(enum ProjectStatus status)
{
	Project::status = status;
}