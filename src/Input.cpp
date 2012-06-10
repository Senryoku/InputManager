#include "Input.hpp"

// #include <iostream>

std::map<std::string, Input*> Input::KeyMap;

Input::Input(std::string Name)
{
	myName = Name;
	Input::KeyMap.insert(std::make_pair(Name, this));
}

Input::~Input()
{
	Input::KeyMap.erase(myName);
}

bool Input::isUsed(std::string Name)
{
	return static_cast<bool>(Input::KeyMap.count(Name));
}

Input* Input::get(std::string Name)
{
	return Input::KeyMap[Name];
}

void Input::updateAll()
{
	for(std::map<std::string, Input*>::iterator it = Input::KeyMap.begin();
		it != Input::KeyMap.end(); it++)
		it->second->update();
}

void Input::deleteAll()
{
	while(!Input::KeyMap.empty())
		delete Input::KeyMap.begin()->second;
}
