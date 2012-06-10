#include "InputManager.hpp"

void InputManager::free()
{
	Action::deleteAll();
	Input::deleteAll();
}

bool InputManager::loadInputFromIni(std::string Path, std::string Name)
{
	IniFile Ini = IniFile();
	if(!Ini.load(Path)) return false;

	if(!Ini.isSection(Name)) return false;
	IniFile::Section* S = Ini.getSection(Name);
	for(IniFile::Section::iterator it = S->begin();
		it != S->end(); it++)
	{
		if(it->second.compare(0,6,"Mouse ") == 0)
		{
			unsigned int MouseButton;
			std::istringstream iss(it->second.substr(6, 2));
			iss >> MouseButton;
			InputManager::add(it->first, static_cast<sf::Mouse::Button>(MouseButton));
		} else if(it->second.compare(0,4,"Joy ") == 0) {
			unsigned int JoyNum, JoyButton;
			std::istringstream iss(it->second.substr(4, 1));
			iss >> JoyNum;
			iss.str(it->second.substr(6, 2));
			iss >> JoyButton;
			InputManager::add(it->first, JoyNum, JoyButton);
		} else if(it->second.compare(0,5,"JoyA ") == 0) {
			unsigned int JoyNum, JoyAxis;
			std::istringstream iss(it->second.substr(5, 1));
			iss >> JoyNum;
			iss.str(it->second.substr(7, 1));
			iss >> JoyAxis;
			InputManager::add(it->first, JoyNum, static_cast<sf::Joystick::Axis>(JoyAxis));
		} else {
			unsigned int Key;
			std::istringstream iss(it->second);
			iss >> Key;
			InputManager::add(it->first, static_cast<sf::Keyboard::Key>(Key));
		}
	}

	return true;
}

bool InputManager::loadActionFromIni(std::string Path, std::string Name)
{
	IniFile Ini = IniFile();
	if(!Ini.load(Path)) return false;

	if(!Ini.isSection(Name)) return false;
	IniFile::Section* S = Ini.getSection(Name);
	for(IniFile::Section::iterator it = S->begin();
		it != S->end(); it++)
	{
		if(it->second.length() > 0)
		{
			unsigned int T;
			std::istringstream iss(it->second.substr(0, 1));
			iss >> T;
			std::string I1 = it->second.substr(2), I2 = "";
			if(I1.find_first_of(" ") < I1.length())
			{
				I2 = I1.substr(I1.find_first_of(" ") + 1);
				I1 = I1.substr(0, I1.find_first_of(" "));
			}
			//std::cout << "Add Action : " << it->first << ", " << T << ", " << it->second.substr(2) << " : "
			//<< Input::isUsed(it->second.substr(2)) << " I1 : " << I1 << " I2 : " << I2 << std::endl;
			InputManager::add(it->first, static_cast<Action::Type>(T), I1, I2);
		}
	}

	return true;
}

bool InputManager::loadFromIni(std::string Path, std::string InputSection, std::string ActionSection)
{
	return InputManager::loadInputFromIni(Path, InputSection) && InputManager::loadActionFromIni(Path, ActionSection);
}

bool InputManager::saveInputToIni(std::string Path, std::string Name)
{
	IniFile File = IniFile();
	File.addSection(Name);
	for(std::map<std::string, Input*>::iterator it = Input::getIterator();
		it != Input::getItEnd(); it++)
		File.addValue(Name, it->first, it->second->getIniStrDesc());

	return File.save(Path);
}

bool InputManager::saveActionToIni(std::string Path, std::string Name)
{
	IniFile File = IniFile();
	File.addSection(Name);
	for(std::map<std::string, Action*>::iterator it = Action::getIterator();
		it != Action::getItEnd(); it++)
	{
		std::string Value = "";
		std::ostringstream SStr;
		SStr << it->second->getType();
		Value +=  SStr.str();
		if(it->second->getInput1() != NULL) Value += it->second->getInput1()->getName();
		if(it->second->getInput2() != NULL) Value += " " + it->second->getInput2()->getName();
		File.addValue(Name, it->first, Value);
	}

	return File.save(Path);
}

bool InputManager::saveToIni(std::string Path, std::string InputSection, std::string ActionSection)
{
	IniFile File = IniFile();

	File.addSection(InputSection);
	for(std::map<std::string, Input*>::iterator it = Input::getIterator();
		it != Input::getItEnd(); it++)
		File.addValue(InputSection, it->first, it->second->getIniStrDesc());

	File.addSection(ActionSection);
	for(std::map<std::string, Action*>::iterator it = Action::getIterator();
		it != Action::getItEnd(); it++)
	{
		std::string Value = "";
		std::ostringstream SStr;
		SStr << it->second->getType();
		Value +=  SStr.str() + " ";
		if(it->second->getInput1() != NULL) Value += it->second->getInput1()->getName();
		if(it->second->getInput2() != NULL) Value += " " + it->second->getInput2()->getName();
		File.addValue(ActionSection, it->first, Value);
	}

	return File.save(Path);
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

Action* InputManager::add(const std::string ActionName, Action::Type Type, std::string I1, std::string I2)
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
