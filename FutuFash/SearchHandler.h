#pragma once
#include "Common.h"

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
	ID, 
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
	SearchField getNewField();
	std::string getNewQuery();
	void setField(SearchField field);
	void setQuery(std::string query);
	std::vector<SearchField> getAllowedFields();
	void printFieldChoice();
	std::vector<Project*> searchInProjects();
	std::vector<User*> searchInUsers();
	std::vector<Designer*> searchInDesigners();
	std::vector<Model*> searchInModels();
public:
	SearchHandler(SearchEntityType type);
	template<typename EntityT> std::vector<EntityT*> getResult();
	void printResult(std::vector<Project*>* result);
	void printResult(std::vector<User*>* result);
	void printResult(std::vector<Designer*>* result);
	void printResult(std::vector<Model*>* result);
};