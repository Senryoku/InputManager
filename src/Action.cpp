#include "Action.hpp"

namespace InputManager
{

std::map<std::string, Action*> Action::Map;

Action::Action(const std::string& ActionName, Type Type, Input* I1, Input* I2) :
	myName(ActionName), myInput1(I1), myInput2(I2), myType(Type)
{
	Action::Map.insert(std::make_pair(ActionName, this));
}

Action::Action(const std::string& ActionName, Type Type, const std::string I1, const std::string I2) :
	myName(ActionName), myType(Type)
{
	if(Input::isUsed(I1)) myInput1 = Input::get(I1); else myInput1 = NULL;
	if(Input::isUsed(I2)) myInput2 = Input::get(I2); else myInput2 = NULL;
	Action::Map.insert(std::make_pair(ActionName, this));
}

Action::~Action()
{
	Action::Map.erase(myName);
}

bool Action::check()
{
	switch(myType)
	{
		case Pressed:
			return ((myInput1 != NULL) ? myInput1->isPressed() : 0) ||
				((myInput2 != NULL) ? myInput2->isPressed() : 0);
			break;
		case JustPressed:
			return ((myInput1 != NULL) ? myInput1->wasJustPressed() : 0) ||
				((myInput2 != NULL) ? myInput2->wasJustPressed() : 0);
			break;
		case JustReleased:
			return ((myInput1 != NULL) ? myInput1->wasJustReleased() : 0) ||
				((myInput2 != NULL) ? myInput2->wasJustReleased() : 0);
			break;
		case Axis: // Permet de vérifier que le seuil a été dépassé
			return ((myInput1 != NULL) ? myInput1->isPressed() : 0) ||
				((myInput2 != NULL) ? myInput2->isPressed() : 0);
			break;
		default:
			return false;
	}
}

float Action::getPosition()
{
	if(myInput1 != NULL && myInput1->getPosition() != 0.f) return myInput1->getPosition();
	if(myInput2 != NULL && myInput2->getPosition() != 0.f) return myInput2->getPosition();
	return 0.f;
}

void Action::setInput(const std::string& InputName, unsigned int Number)
{
	if(!Input::isUsed(InputName)) return;
	if(Number > 0)
		myInput1 = Input::get(InputName);
	else
		myInput2 = Input::get(InputName);
}

void Action::setInput(Input* I, unsigned int Number)
{
	if(Number > 0)
		myInput1 = I;
	else
		myInput2 = I;
}

void Action::addInput(const std::string& InputName)
{
	if(!Input::isUsed(InputName)) return;
	if(myInput1 == NULL)
		myInput1 = Input::get(InputName);
	else
		myInput2 = Input::get(InputName);
}

void Action::addInput(Input* I)
{
	if(myInput1 == NULL)
		myInput1 = I;
	else
		myInput2 = I;
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
