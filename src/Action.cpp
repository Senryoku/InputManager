#include "Action.hpp"

#include <iostream>

namespace InputManager
{

std::map<std::string, Action*> Action::Map;

Action::Action(const std::string& ActionName, Type Type, const std::string I1, const std::string I2) :
	myName(ActionName), myType(Type)
{
	if(Input::isUsed(I1)) myInput1 = I1;
	if(Input::isUsed(I2)) myInput2 = I2;
	Action::Map.insert(std::make_pair(ActionName, this));
}

Action::~Action()
{
	Action::Map.erase(myName);
}

bool Action::check()
{
	Input* I1 = Input::get(myInput1);
	Input* I2 = Input::get(myInput2);
	bool B = false;
	switch(myType)
	{
		case Pressed:
			if(I1 != NULL) B = I1->isPressed();
			if(I2 != NULL) B += I2->isPressed();
			break;
		case JustPressed:
			if(I1 != NULL) B = I1->wasJustPressed();
			if(I2 != NULL) B += I2->wasJustPressed();
			break;
		case JustReleased:
			if(I1 != NULL) B = I1->wasJustReleased();
			if(I2 != NULL) B += I2->wasJustReleased();
			break;
		case Axis: // Permet de vérifier que le seuil a été dépassé
			if(I1 != NULL) B = I1->isPressed();
			if(I2 != NULL) B += I2->isPressed();
			break;
		default:
			return false;
	}
	return B;
}

float Action::getPosition()
{
	if(myInput1 != "" && Input::get(myInput1)->getPosition() != 0.f) return Input::get(myInput1)->getPosition();
	if(myInput2 != "" && Input::get(myInput2)->getPosition() != 0.f) return Input::get(myInput2)->getPosition();
	return 0.f;
}

void Action::setInput(const std::string& InputName, unsigned int Number)
{
	if(!Input::isUsed(InputName)) return;
	if(Number > 0)
		myInput1 = InputName;
	else
		myInput2 = InputName;
}

void Action::addInput(const std::string& InputName)
{
	if(!Input::isUsed(InputName)) return;
	if(myInput1 == "")
		myInput1 = InputName;
	else
		myInput2 = InputName;
}

bool Action::check(const std::string& ActionName)
{
	if(Action::Map.count(ActionName) != 1) return false;
	return Action::Map[ActionName]->check();
}

float Action::getPosition(const std::string& ActionName)
{
	if(Action::Map.count(ActionName) != 1) return false;
	return Action::Map.find(ActionName)->second->getPosition();
}

Action* Action::get(const std::string& ActionName)
{
	return Action::Map[ActionName];
}

void Action::deleteAll()
{
	while(!Action::Map.empty())
		delete Action::Map.begin()->second;
}

} // Namespace InputManager
