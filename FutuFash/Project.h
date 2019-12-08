#pragma once
#include "Entity.h"
#include "Designer.h"
#include "Model.h"
enum ProjectStatus 
{
	INSEARCH, FILLED, FINISHED, DELETED
};
class Project :
	public Entity

{
private:
	int id;
	string name;
	string date;
	string location;
	Designer* designer;
	map<int, Model*> models;
	enum ProjectStatus status;

public:
	string getName();
	int getId();
	string getDate();
	string getLocation();
	Designer* getDesigner();
	map<int, Model*> getModels();
	enum ProjectStatus getStatus();

	void setDate(string date);
	void setLocation(string location);
	void addModel(Model* model);
	void removeModel(Model* model);
	void setStatus(enum ProjectStatus);
	void setDesigner(Designer* designer);



};

