//TODO DELETE

#pragma once
#include "Common.h"
#include "Model.h"
#include "Designer.h"

class Entity;
class Designer;
class Model;


enum ProjectStatus 
{
	INSEARCH, FILLED, FINISHED, DELETED
};
class Project :
	public Entity

{
private:
	int id;
	std::string name;
	std::string date;
	std::string location;
	Designer* designer;
	std::map<int, Model*> models;
	enum ProjectStatus status;

public:
	std::string getName();
	int getId();
	std::string getDate();
	std::string getLocation();
	Designer* getDesigner();
	std::map<int, Model*> getModels();
	enum ProjectStatus getStatus();

	void setDate(std::string date);
	void setLocation(std::string location);
	void addModel(Model* model);
	void removeModel(Model* model);
	void setStatus(enum ProjectStatus);
	void setDesigner(Designer* designer);



};

