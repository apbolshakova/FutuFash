#pragma once
#include "Common.h"


enum ProjectStatus
{
	INSEARCH, FILLED, FINISHED, DELETED
};


class Project;
class User;
class Designer;
class Model;


class Entity
{
protected:
	int id;
	std::string name;
public:
	Entity(int id = -1, std::string name = "") : id(id), name(name) {};

	int getId() { return this->id; }
	std::string getName() { return this->name; }

	void setId(int id);
	void setName(std::string name = "");
};


class Project :
	public Entity

{
private:
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


class User :
	public Entity
{

private:
	int experienceInYears;
	std::map<int, Project*> *projects;
	bool toDelete;
public:
	User(int experienceInYears = -1, std::map<int, Project*> *projects = nullptr, bool toDelete = false) : experienceInYears(experienceInYears),projects(projects), toDelete(toDelete) {};
	int getExp();
	std::map<int, Project*>* getProjects();
	bool isDeleted();
	void setExp(int exp);
	void addProject(Project* project);
	void removeProject(Project* project);
	void markToDelete();
	virtual ~User() {};
};

class Designer :
	public User
{
private:
	std::string vogue;

public:
	Designer(std::string vogue = "") : vogue(vogue) {};
	std::string getVogue();
	void setVogue(std::string vogue);

};


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