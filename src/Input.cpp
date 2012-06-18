#include "Input.hpp"


namespace InputManager
{

std::map<std::string, Input*> Input::KeyMap;

Input::Input(const std::string& Name)
{
	myName = Name;
	std::map<std::string, Input*>::iterator it = Input::KeyMap.find(Name);
	if(it != Input::KeyMap.end()) delete it->second;
	Input::KeyMap.insert(std::make_pair(Name, this));
}

Input::~Input()
{
	Input::KeyMap.erase(myName);
}

bool Input::isUsed(const std::string& Name)
{
	return static_cast<bool>(Input::KeyMap.count(Name));
}

Input* Input::get(const std::string& Name)
{
	std::map<std::string, Input*>::iterator it = Input::KeyMap.find(Name);
	if(it != Input::KeyMap.end()) return it->second; else return NULL;
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

} // Namespace InputManager
