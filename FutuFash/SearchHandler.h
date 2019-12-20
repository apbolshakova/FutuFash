#pragma once
#include "Common.h"
#include "Entities.h"

class Project;
class User;
class Designer;
class Model;

enum SearchEntityType
{
	PRJ,
	USR,
	DSG,
	MDL
};

enum SearchField
{
	ID = 1, 
	NAME, 
	DATE, 
	LOCATION, 
	DESIGNER, 
	STATUS, 
	EXPERIENCE, 
	TYPE,
	VOGUE,
	HEIGHT,
	WEIGHT,
	HAIR_COLOR
};

class SearchHandler
{
private:
	SearchEntityType type;
	SearchField field;
	std::string query;
	std::map<int, User*> *users;
	std::map<int, Project*> *projects;
	SearchField getNewField();
	std::string getNewQuery();
	bool queryIsValid(std::string query);
	void setField(SearchField field);
	void setQuery(std::string query);
	std::vector<SearchField> getAllowedFields();
	void printFieldChoice();
public:
	SearchHandler(SearchEntityType type, std::map<int, User*> *users, 
		std::map<int, Project*> *projects);

	void getResult(std::vector<Project*>& result);
	void getResult(std::vector<User*>& result);
	void getResult(std::vector<Designer*>& result);
	void getResult(std::vector<Model*>& result);

	void printResult(std::vector<Project*>& result);
	void printResult(std::vector<User*>& result);
	void printResult(std::vector<Designer*>& result);
	void printResult(std::vector<Model*>& result);
};