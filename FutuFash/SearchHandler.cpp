#include "SearchHandler.h"


SearchHandler::SearchHandler(SearchEntityType type)
{
	this->type = type;
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
		it = find(allowedFields.begin(), allowedFields.end(), SearchField(field));
	} while (it == allowedFields.end());
	return SearchField(field);
}


std::vector<SearchField> SearchHandler::getAllowedFields()
{
	std::vector<SearchField> allowed;
	allowed.push_back(ID);
	allowed.push_back(NAME);
	if (this->type == PROJECT)
	{
		allowed.push_back(DATE);
		allowed.push_back(LOCATION);
		allowed.push_back(DESIGNER);
		allowed.push_back(STATUS);
	}
	else
	{
		allowed.push_back(EXPERIENCE);
		if (this->type == DESIGNER)
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
	if (this->type == PROJECT)
	{
		std::cout << DATE << " - date" << std::endl
			<< LOCATION << " - location" << std::endl
			<< DESIGNER << " - designer" << std::endl
			<< STATUS << " - project status" << std::endl;
	}
	else
	{
		std::cout << EXPERIENCE << " - experience in years" << std::endl;
		if (this->type == DESIGNER)
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
	//TODO
}


void SearchHandler::setField(SearchField field)
{
	this->field = field;
}


void SearchHandler::setQuery(std::string query)
{
	this->query = query;
}


template <typename EntityT>
std::vector<EntityT*> SearchHandler::getResult()
{
	switch (this->searchType)
	{
	case PROJECT: return this->searchInProjects(); break;
	case USER: return this->searchInUsers(); break;
	case DESIGNER: return this->searchInDesigners(); break;
	case MODEL: return this->searchInModels(); break;
	default: break;
	}
}


std::vector<Project*> SearchHandler::searchInProjects()
{
	std::vector<Project*> result;
	//TODO
	return result;
}


std::vector<User*> SearchHandler::searchInUsers()
{
	std::vector<User*> result;
	//TODO
	return result;
}


std::vector<Designer*> SearchHandler::searchInDesigners()
{
	std::vector<Designer*> result;
	//TODO
	return result;
}


std::vector<Model*> SearchHandler::searchInModels()
{
	std::vector<Model*> result;
	//TODO
	return result;
}


void SearchHandler::printResult(std::vector<Project*>* result)
{
	//TODO
}


void SearchHandler::printResult(std::vector<User*>* result)
{
	//TODO
}


void SearchHandler::printResult(std::vector<Designer*>* result)
{
	//TODO
}


void SearchHandler::printResult(std::vector<Model*>* result)
{
	//TODO
}