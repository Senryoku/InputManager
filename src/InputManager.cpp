#include "InputManager.hpp"

#include <iostream>

namespace InputManager
{

sf::Keyboard::Key convertStrToKey(const std::string& Str);

void free()
{
	Action::deleteAll();
	Input::deleteAll();
}

bool loadInputFromIni(const std::string& Path, const std::string& Name)
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
			if(MouseButton < sf::Mouse::ButtonCount)
				add(it->first, static_cast<sf::Mouse::Button>(MouseButton));
		} else if(it->second.compare(0,4,"Joy ") == 0) {
			unsigned int JoyNum, JoyButton;
			std::istringstream iss(it->second.substr(4, 1));
			iss >> JoyNum;
			std::istringstream iss2(it->second.substr(6, 2));
			iss2 >> JoyButton;
			if(JoyNum < sf::Joystick::Count && JoyButton < sf::Joystick::ButtonCount)
				add(it->first, JoyNum, JoyButton);
		} else if(it->second.compare(0,5,"JoyA ") == 0) {
			unsigned int JoyNum, JoyAxis;
			std::istringstream iss(it->second.substr(5, 1));
			iss >> JoyNum;
			std::istringstream iss2(it->second.substr(7, 1));
			iss2 >> JoyAxis;
			if(JoyNum < sf::Joystick::Count && JoyAxis < sf::Joystick::AxisCount)
			{
				if(it->second.length() > 8) // Seuil à récupérer
				{
					float T;
					std::istringstream iss3(it->second.substr(9));
					iss3 >> T;
					add(it->first, JoyNum, static_cast<sf::Joystick::Axis>(JoyAxis), T);
				} else {
					add(it->first, JoyNum, static_cast<sf::Joystick::Axis>(JoyAxis));
				}
			}
		} else {
			if(it->second[0] >= '0' && it->second[0] <= '9')
			{
				unsigned int Key;
				std::istringstream iss(it->second);
				iss >> Key;
				if(Key < sf::Keyboard::KeyCount)
					add(it->first, static_cast<sf::Keyboard::Key>(Key));
			} else {
				sf::Keyboard::Key K = convertStrToKey(it->second.substr(0, it->second.find_first_of(" ")));
				if(K != sf::Keyboard::KeyCount) add(it->first, K);
				//std::cout << "AddedKey " << it->first << " " << K << std::endl;
			}
		}
	}

	return true;
}

bool loadActionFromIni(const std::string& Path, const std::string& Name)
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
			std::cout << "Add Action : " << it->first << ", " << T << ", " << it->second.substr(2) << " : "
			<< Input::isUsed(it->second.substr(2)) << " I1 : " << I1 << " I2 : " << I2 << std::endl;
			add(it->first, static_cast<Action::Type>(T), I1, I2);
		}
	}

	return true;
}

bool loadFromIni(const std::string& Path, const std::string& InputSection, const std::string& ActionSection)
{
	return loadInputFromIni(Path, InputSection) && loadActionFromIni(Path, ActionSection);
}

bool saveInputToIni(const std::string& Path, const std::string& Name)
{
	IniFile File = IniFile();
	File.addSection(Name);
	for(std::map<std::string, Input*>::iterator it = Input::getIterator();
		it != Input::getItEnd(); it++)
		File.addValue(Name, it->first, it->second->getIniStrDesc());

	return File.save(Path);
}

bool saveActionToIni(const std::string& Path, const std::string& Name)
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
		Value += it->second->getInput1();
		Value += it->second->getInput2();
		File.addValue(Name, it->first, Value);
	}

	return File.save(Path);
}

bool saveToIni(const std::string& Path, const std::string& InputSection, const std::string& ActionSection)
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
		Value += it->second->getInput1();
		Value += it->second->getInput2();
		File.addValue(ActionSection, it->first, Value);
	}

	return File.save(Path);
}

void setGlobalThreshold(float T)
{
	for(std::map<std::string, Input*>::iterator it = Input::getIterator();
		it != Input::getItEnd(); it++)
		it->second->setThreshold(T);
}

Keyboard* add(const std::string& Name, sf::Keyboard::Key KeyID)
{
	return new Keyboard(Name, KeyID);
}

Mouse* add(const std::string& Name, sf::Mouse::Button ButID)
{
	return new Mouse(Name, ButID);
}

Joystick* add(const std::string& Name, unsigned int JoyID, unsigned int ButID)
{
	if(sf::Joystick::isConnected(JoyID) && sf::Joystick::getButtonCount(JoyID) > ButID)
		return new Joystick(Name, JoyID, ButID);
	else return NULL;
}

Axis* add(const std::string& Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T)
{
	if(sf::Joystick::isConnected(JoyID) && sf::Joystick::hasAxis(JoyID, AxisID))
		return new Axis(Name, JoyID, AxisID, T);
	else return NULL;
}

Action* add(const std::string& ActionName, Action::Type Type, std::string I1, std::string I2)
{
	return new Action(ActionName, Type, I1, I2);
}

bool check(const std::string& ActionName)
{
	return Action::check(ActionName);
}

float getPosition(const std::string& ActionName)
{
	return Action::getPosition(ActionName);
}

Input* createInput(sf::Window& W, const std::string& Name)
{
	if(!W.isOpen()) return NULL;
	sf::Event event;
	while (W.pollEvent(event)) {} // On vide la pile d'événements
	while(W.isOpen()) // Si la fenêtre n'est pas ouverte, il ne peut y avoir d'event
	{
		while (W.waitEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::Escape:
						return NULL;
						break;
					default:
						return add(Name, event.key.code);
						break;
				}
			}

			if(event.type == sf::Event::MouseButtonPressed)
			{
				return add(Name, event.mouseButton.button);
			}

			if(event.type == sf::Event::JoystickButtonPressed)
			{
				std::cout << event.joystickButton.joystickId << " " << event.joystickButton.button << std::endl;
				return add(Name, event.joystickButton.joystickId, event.joystickButton.button);
			}

			if(event.type == sf::Event::JoystickMoved && (event.joystickMove.position > 50.f || event.joystickMove.position < -50.f))
			{
				return add(Name, event.joystickMove.joystickId, event.joystickMove.axis);
			}
			//std::cout << "Event" << std::endl;
		}
		//std::cout << "NoEvent" << std::endl;
		sf::sleep(sf::milliseconds(10));
	}
	return NULL;
}

sf::Keyboard::Key convertStrToKey(const std::string& Str)
{
	if(Str.compare("A") == 0) return sf::Keyboard::A;
	if(Str.compare("B") == 0) return sf::Keyboard::B;
	if(Str.compare("C") == 0) return sf::Keyboard::C;
	if(Str.compare("D") == 0) return sf::Keyboard::D;
	if(Str.compare("E") == 0) return sf::Keyboard::E;
	if(Str.compare("F") == 0) return sf::Keyboard::F;
	if(Str.compare("G") == 0) return sf::Keyboard::G;
	if(Str.compare("H") == 0) return sf::Keyboard::H;
	if(Str.compare("I") == 0) return sf::Keyboard::I;
	if(Str.compare("J") == 0) return sf::Keyboard::J;
	if(Str.compare("K") == 0) return sf::Keyboard::K;
	if(Str.compare("L") == 0) return sf::Keyboard::L;
	if(Str.compare("M") == 0) return sf::Keyboard::M;
	if(Str.compare("N") == 0) return sf::Keyboard::N;
	if(Str.compare("O") == 0) return sf::Keyboard::O;
	if(Str.compare("P") == 0) return sf::Keyboard::P;
	if(Str.compare("Q") == 0) return sf::Keyboard::Q;
	if(Str.compare("R") == 0) return sf::Keyboard::R;
	if(Str.compare("S") == 0) return sf::Keyboard::S;
	if(Str.compare("T") == 0) return sf::Keyboard::T;
	if(Str.compare("U") == 0) return sf::Keyboard::U;
	if(Str.compare("V") == 0) return sf::Keyboard::V;
	if(Str.compare("W") == 0) return sf::Keyboard::W;
	if(Str.compare("X") == 0) return sf::Keyboard::X;
	if(Str.compare("Y") == 0) return sf::Keyboard::Y;
	if(Str.compare("Z") == 0) return sf::Keyboard::Z;
	if(Str.compare("Num0") == 0) return sf::Keyboard::Num0;
	if(Str.compare("Num1") == 0) return sf::Keyboard::Num1;
	if(Str.compare("Num2") == 0) return sf::Keyboard::Num2;
	if(Str.compare("Num3") == 0) return sf::Keyboard::Num3;
	if(Str.compare("Num4") == 0) return sf::Keyboard::Num4;
	if(Str.compare("Num5") == 0) return sf::Keyboard::Num5;
	if(Str.compare("Num6") == 0) return sf::Keyboard::Num6;
	if(Str.compare("Num7") == 0) return sf::Keyboard::Num7;
	if(Str.compare("Num8") == 0) return sf::Keyboard::Num8;
	if(Str.compare("Num9") == 0) return sf::Keyboard::Num9;
	if(Str.compare("Escape") == 0) return sf::Keyboard::Escape;
	if(Str.compare("LControl") == 0) return sf::Keyboard::LControl;
	if(Str.compare("LShift") == 0) return sf::Keyboard::LShift;
	if(Str.compare("LAlt") == 0) return sf::Keyboard::LAlt;
	if(Str.compare("LSystem") == 0) return sf::Keyboard::LSystem;
	if(Str.compare("RControl") == 0) return sf::Keyboard::RControl;
	if(Str.compare("RShift") == 0) return sf::Keyboard::RShift;
	if(Str.compare("RAlt") == 0) return sf::Keyboard::RAlt;
	if(Str.compare("RSystem") == 0) return sf::Keyboard::RSystem;
	if(Str.compare("Menu") == 0) return sf::Keyboard::Menu;
	if(Str.compare("LBracket") == 0) return sf::Keyboard::LBracket;
	if(Str.compare("RBracket") == 0) return sf::Keyboard::RBracket;
	if(Str.compare("SemiColon") == 0) return sf::Keyboard::SemiColon;
	if(Str.compare("Comma") == 0) return sf::Keyboard::Comma;
	if(Str.compare("Period") == 0) return sf::Keyboard::Period;
	if(Str.compare("Quote") == 0) return sf::Keyboard::Quote;
	if(Str.compare("Slash") == 0) return sf::Keyboard::Slash;
	if(Str.compare("BackSlash") == 0) return sf::Keyboard::BackSlash;
	if(Str.compare("Tilde") == 0) return sf::Keyboard::Tilde;
	if(Str.compare("Equal") == 0) return sf::Keyboard::Equal;
	if(Str.compare("Dash") == 0) return sf::Keyboard::Dash;
	if(Str.compare("Space") == 0) return sf::Keyboard::Space;
	if(Str.compare("Return") == 0) return sf::Keyboard::Return;
	if(Str.compare("Back") == 0) return sf::Keyboard::Back;
	if(Str.compare("Tab") == 0) return sf::Keyboard::Tab;
	if(Str.compare("PageUp") == 0) return sf::Keyboard::PageUp;
	if(Str.compare("PageDown") == 0) return sf::Keyboard::PageDown;
	if(Str.compare("End") == 0) return sf::Keyboard::End;
	if(Str.compare("Home") == 0) return sf::Keyboard::Home;
	if(Str.compare("Insert") == 0) return sf::Keyboard::Insert;
	if(Str.compare("Delete") == 0) return sf::Keyboard::Delete;
	if(Str.compare("Add") == 0) return sf::Keyboard::Add;
	if(Str.compare("Subtract") == 0) return sf::Keyboard::Subtract;
	if(Str.compare("Multiply") == 0) return sf::Keyboard::Multiply;
	if(Str.compare("Divide") == 0) return sf::Keyboard::Divide;
	if(Str.compare("Left") == 0) return sf::Keyboard::Left;
	if(Str.compare("Right") == 0) return sf::Keyboard::Right;
	if(Str.compare("Up") == 0) return sf::Keyboard::Up;
	if(Str.compare("Down") == 0) return sf::Keyboard::Down;
	if(Str.compare("Numpad0") == 0) return sf::Keyboard::Numpad0;
	if(Str.compare("Numpad1") == 0) return sf::Keyboard::Numpad1;
	if(Str.compare("Numpad2") == 0) return sf::Keyboard::Numpad2;
	if(Str.compare("Numpad3") == 0) return sf::Keyboard::Numpad3;
	if(Str.compare("Numpad4") == 0) return sf::Keyboard::Numpad4;
	if(Str.compare("Numpad5") == 0) return sf::Keyboard::Numpad5;
	if(Str.compare("Numpad6") == 0) return sf::Keyboard::Numpad6;
	if(Str.compare("Numpad7") == 0) return sf::Keyboard::Numpad7;
	if(Str.compare("Numpad8") == 0) return sf::Keyboard::Numpad8;
	if(Str.compare("Numpad9") == 0) return sf::Keyboard::Numpad9;
	if(Str.compare("F1") == 0) return sf::Keyboard::F1;
	if(Str.compare("F2") == 0) return sf::Keyboard::F2;
	if(Str.compare("F3") == 0) return sf::Keyboard::F3;
	if(Str.compare("F4") == 0) return sf::Keyboard::F4;
	if(Str.compare("F5") == 0) return sf::Keyboard::F5;
	if(Str.compare("F6") == 0) return sf::Keyboard::F6;
	if(Str.compare("F7") == 0) return sf::Keyboard::F7;
	if(Str.compare("F8") == 0) return sf::Keyboard::F8;
	if(Str.compare("F9") == 0) return sf::Keyboard::F9;
	if(Str.compare("F10") == 0) return sf::Keyboard::F10;
	if(Str.compare("F11") == 0) return sf::Keyboard::F11;
	if(Str.compare("F12") == 0) return sf::Keyboard::F12;
	if(Str.compare("F13") == 0) return sf::Keyboard::F13;
	if(Str.compare("F14") == 0) return sf::Keyboard::F14;
	if(Str.compare("F15") == 0) return sf::Keyboard::F15;
	if(Str.compare("Pause") == 0) return sf::Keyboard::Pause;
	return sf::Keyboard::KeyCount;
}

void update()
{
	Input::updateAll();
}

} // Namespace InputManager
