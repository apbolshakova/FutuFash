#pragma once
#include "SearchHandler.h"

SearchHandler::SearchHandler(SearchEntityType type, std::map<int, User*> *users, 
	std::map<int, Project*> *projects)
{
	this->type = type;
	this->users = users;
	this->projects = projects;
	this->setField(this->getNewField());
	this->setQuery(this->getNewQuery());
}


SearchField SearchHandler::getNewField()
{
	system("cls");
	
	std::vector<SearchField> allowedFields = getAllowedFields();
	this->printFieldChoice();
	int field;
	std::vector<SearchField>::iterator it;

	do
	{
		std::cin >> field;
		if (field != 0)
		{
			it = find(allowedFields.begin(), allowedFields.end(), SearchField(field));
		}
		else it = allowedFields.end();
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (it == allowedFields.end());
	return SearchField(field);
}


std::vector<SearchField> SearchHandler::getAllowedFields()
{
	std::vector<SearchField> allowed;
	allowed.push_back(ID);
	allowed.push_back(NAME);
	if (this->type == PRJ)
	{
		allowed.push_back(DATE);
		allowed.push_back(LOCATION);
		allowed.push_back(DESIGNER);
		allowed.push_back(STATUS);
	}
	else
	{
		allowed.push_back(EXPERIENCE);
		if (this->type == DSG)
		{
			allowed.push_back(VOGUE);
		}
		else
		{
			allowed.push_back(HEIGHT);
			allowed.push_back(WEIGHT);
			allowed.push_back(HAIR_COLOR);
		}
	}
	return allowed;
}


void SearchHandler::printFieldChoice()
{
	std::cout << "Enter by which parameter you want to search: " << std::endl;
	std::cout << ID << " - ID" << std::endl
		<< NAME << " - name" << std::endl;
	if (this->type == PRJ)
	{
		std::cout << DATE << " - date" << std::endl
			<< LOCATION << " - location" << std::endl
			<< DESIGNER << " - designer" << std::endl
			<< STATUS << " - project status" << std::endl;
	}
	else
	{
		std::cout << EXPERIENCE << " - experience in years" << std::endl;
		if (this->type == DSG)
		{
			std::cout << VOGUE << " - vogue" << std::endl;
		}
		else
		{
			std::cout << HEIGHT << " - height" << std::endl
				<< WEIGHT << " - weight" << std::endl
				<< HAIR_COLOR << " - hair color" << std::endl;
		}
	}
	std::cout << std::endl;
}


std::string SearchHandler::getNewQuery()
{
	std::string q;
	std::cout << "Enter value to search: " << std::endl;

	if (this->field == ID || this->field == EXPERIENCE || this->field == HEIGHT ||
		this->field == WEIGHT)
	{
		std::cout << "Only positive numbers are allowed." << std::endl;
	}

	if (this->field == STATUS)
	{
		std::cout << INSEARCH << " - searching for models" << std::endl;
		std::cout << FILLED << " - filled with attendants and currently in process" << std::endl;
		std::cout << FINISHED << " - held" << std::endl;
	}
	do
	{
		std::getline(std::cin, q);
	} while (q.empty() || !this->queryIsValid(q));
	return q;
}


bool SearchHandler::queryIsValid(std::string query)
{
	if (this->field == ID || this->field == EXPERIENCE || this->field == HEIGHT ||
		this->field == WEIGHT)
	{
		return !query.empty() && query.find_first_not_of("0123456789") == std::string::npos;
	}
	else if (this->field == STATUS)
	{
		return (query == std::to_string(INSEARCH) || query == std::to_string(FILLED) ||
			query == std::to_string(FINISHED));
	}
	return true;
}


void SearchHandler::setField(SearchField field)
{
	this->field = field;
}


void SearchHandler::setQuery(std::string query)
{
	this->query = query;
}


void SearchHandler::getResult(std::vector<Project*>& result)
{

}


void SearchHandler::getResult(std::vector<User*>& result)
{
	//TODO
}


void SearchHandler::getResult(std::vector<Designer*>& result)
{
	//TODO
}


void SearchHandler::getResult(std::vector<Model*>& result)
{
	//TODO
}

void SearchHandler::printResult(std::vector<Project*>& result)
{
	//TODO
}


void SearchHandler::printResult(std::vector<User*>& result)
{
	//TODO
}


void SearchHandler::printResult(std::vector<Designer*>& result)
{
	//TODO
}


void SearchHandler::printResult(std::vector<Model*>& result)
{
	//TODO
}