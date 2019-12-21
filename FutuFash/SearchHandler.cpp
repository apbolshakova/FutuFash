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
		else if (this->type == MDL)
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
			<< DESIGNER << " - name of designer" << std::endl
			<< STATUS << " - project status" << std::endl;
	}
	else
	{
		std::cout << EXPERIENCE << " - experience in years" << std::endl;
		if (this->type == DSG)
		{
			std::cout << VOGUE << " - vogue" << std::endl;
		}
		else if (this->type == MDL)
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

//TODO: firstly check type

void SearchHandler::getResult(std::vector<Project*>& result)
{
	for (auto const& el : *(this->projects))
	{
		if (this->field == ID)
		{
			if (el.first == stoi(this->query)) result.push_back(el.second);
		}
		if (this->field == NAME)
		{
			if (el.second->getName() == this->query) result.push_back(el.second);
		}
		if (this->field == DATE)
		{
			if (el.second->getDate() == this->query) result.push_back(el.second);
		}
		if (this->field == LOCATION)
		{
			if (el.second->getLocation() == this->query) result.push_back(el.second);
		}
		if (this->field == DESIGNER)
		{
			if (el.second->getDesigner()->getName() == this->query) result.push_back(el.second);
		}
		if (this->field == STATUS)
		{
			if (el.second->getStatus() == stoi(this->query)) result.push_back(el.second);
		}
	}
}


void SearchHandler::getResult(std::vector<User*>& result)
{
	for (auto const& el : *(this->users))
	{
		if (this->field == ID)
		{
			if (el.first == stoi(this->query)) result.push_back(el.second);
		}
		if (this->field == NAME)
		{
			if (el.second->getName() == this->query) result.push_back(el.second);
		}
		if (this->field == EXPERIENCE)
		{
			if (el.second->getExp() == stoi(this->query)) result.push_back(el.second);
		}
	}
}


void SearchHandler::getResult(std::vector<Designer*>& result)
{
	for (auto const& el : *(this->users))
	{
		Designer* elem = dynamic_cast<Designer*>(el.second);
		if (elem == nullptr) continue;
		if (this->field == ID)
		{
			if (el.first == stoi(this->query)) 
				result.push_back(elem);
		}
		if (this->field == NAME)
		{
			if (el.second->getName() == this->query) 
				result.push_back(elem);
		}
		if (this->field == EXPERIENCE)
		{
			if (el.second->getExp() == stoi(this->query)) 
				result.push_back(elem);
		}
		if (this->field == VOGUE)
		{
			if (elem->GetVogue() == this->query)
				result.push_back(elem);
		}
	}
}


void SearchHandler::getResult(std::vector<Model*>& result)
{
	for (auto const& el : *(this->users))
	{
		Model* elem = dynamic_cast<Model*>(el.second);
		if (elem == nullptr) continue;
		if (this->field == ID)
		{
			if (el.first == stoi(this->query))
				result.push_back(elem);
		}
		if (this->field == NAME)
		{
			if (el.second->getName() == this->query)
				result.push_back(elem);
		}
		if (this->field == EXPERIENCE)
		{
			if (el.second->getExp() == stoi(this->query))
				result.push_back(elem);
		}
		if (this->field == HEIGHT)
		{
			if (elem->getHeight() == stoi(this->query))
				result.push_back(elem);
		}
		if (this->field == WEIGHT)
		{
			if (elem->getWeight() == stoi(this->query))
				result.push_back(elem);
		}
		if (this->field == HAIR_COLOR)
		{
			if (elem->getHairColor() == this->query)
				result.push_back(elem);
		}
	}
}

void SearchHandler::printResult(std::vector<Project*>& result)
{
	if (result.size() == 0)
	{
		std::cout << "No matching projects found." << std::endl;
		return;
	}

	for (std::size_t i = 0; i < result.size(); ++i)
		std::cout << i << ") " << result[i]->getName() << " with " << 
		result[i]->getDesigner()->getName() << " as designer" << std::endl;
}


void SearchHandler::printResult(std::vector<User*>& result)
{
	if (result.size() == 0)
	{
		std::cout << "No matching users found." << std::endl;
		return;
	}

	for (std::size_t i = 0; i < result.size(); ++i)
		std::cout << i << ") " << result[i]->getName() << " with " << result[i]->getExp()
		<< " years experience" << std::endl;
}


void SearchHandler::printResult(std::vector<Designer*>& result)
{
	if (result.size() == 0)
	{
		std::cout << "No matching designers found." << std::endl;
		return;
	}

	for (std::size_t i = 0; i < result.size(); ++i)
		std::cout << i << ") " << result[i]->getName() << " with " <<
		result[i]->getExp() << " years experience from " << result[i]->GetVogue() << " vogue"
		<< std::endl;
}


void SearchHandler::printResult(std::vector<Model*>& result)
{
	if (result.size() == 0)
	{
		std::cout << "No matching models found." << std::endl;
		return;
	}

	for (std::size_t i = 0; i < result.size(); ++i)
		std::cout << i << ") " << result[i]->getName() << " with " <<
		result[i]->getExp() << " years experience: " << result[i]->getHeight() << " tall with "
        << result[i]->getHairColor() << " hair" << std::endl;
}