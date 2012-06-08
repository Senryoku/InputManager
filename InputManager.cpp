#include "InputManager.hpp"

std::string InputManager::myLoadedFile;

InputManager::InputManager()
{
}

InputManager::InputManager(std::string Path)
{
	if(InputManager::loadFromIni(Path))
		InputManager::myLoadedFile = Path;
}

InputManager::~InputManager()
{
	Action::deleteAll();
	Input::deleteAll();
}

bool InputManager::loadFromIni(std::string Path)
{
	Action::deleteAll();
	Input::deleteAll();
	// Chargement...
	InputManager::myLoadedFile = Path;
	return true;
}

Keyboard* InputManager::add(std::string Name, sf::Keyboard::Key KeyID)
{
	return new Keyboard(Name, KeyID);
}

Mouse* InputManager::add(std::string Name, sf::Mouse::Button ButID)
{
	return new Mouse(Name, ButID);
}

Joystick* InputManager::add(std::string Name, unsigned int JoyID, unsigned int ButID)
{
	if(sf::Joystick::isConnected(JoyID) && sf::Joystick::getButtonCount(JoyID) > ButID)
		return new Joystick(Name, JoyID, ButID);
	else return NULL;
}

Axis* InputManager::add(std::string Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T)
{
	if(sf::Joystick::isConnected(JoyID) && sf::Joystick::hasAxis(JoyID, AxisID))
		return new Axis(Name, JoyID, AxisID, T);
	else return NULL;
}

Action* InputManager::add(const std::string ActionName, Action::Type Type, Input* I1, Input* I2)
{
	return new Action(ActionName, Type, I1, I2);
}

bool InputManager::check(const std::string ActionName)
{
	return Action::check(ActionName);
}

float InputManager::getPosition(const std::string ActionName)
{
	return Action::getPosition(ActionName);
}
