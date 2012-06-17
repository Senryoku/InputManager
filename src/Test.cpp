#include <iostream>

#include "InputManager.hpp"

using namespace InputManager;

int main(void)
{
//	add("Test1", sf::Keyboard::A);
//	add("Test2", sf::Keyboard::E);
//	add("Test3", sf::Keyboard::R);
//	add("Test3445", sf::Keyboard::R);
//	add("Escape1", sf::Keyboard::Escape);

//	add("TestMouse", sf::Mouse::Left);
//
//	Axis Ax("Move", 0, sf::Joystick::X, 15.f);
//
//	Joystick Joy1("Jump", 0, 0);
//	loadInputFromIni("Config.ini", "Input");

//	Action B("Test", Action::Pressed, "Test1", "Test2");
//	Action A("Escape", Action::JustPressed, "Escape1");
//	Action C("TestJust", Action::JustPressed, "Test3");
//	Action D("TestJustR", Action::JustReleased, "Test3");
//	Action G("TestMouse", Action::JustReleased, "TestMouse");
//	Action F("TestAxis", Action::Axis, "Move");
//	Action Jump("Jump", Action::JustPressed, "Jump");
//	loadActionFromIni("Config.ini", "Action");

	sf::Joystick::update(); // Necessaire sans fenêtre
	loadFromIni("Config.ini");

	while(!check("Escape"))
	{
		sf::Joystick::update(); // Necessaire sans fenêtre
		update(); // Mise à jour des inputs
		if(check("Test"))
			std::cout << "Test a ete declenche" << std::endl;
		if(check("TestStr"))
			std::cout << "TestStr a ete declenche" << std::endl;
		if(check("TestJust"))
			std::cout << "TestJust a ete declenche" << std::endl;
		if(check("TestJustR"))
			std::cout << "TestJustR a ete declenche" << std::endl;
		if(check("TestMouse"))
			std::cout << "TestMouse a ete declenche" << std::endl;
		if(check("IniTest"))
		{
			std::cout << "IniTest a ete declenche : Test de la sauvegarde..." << std::endl;
			InputManager::saveInputToIni("SavingInputTest.ini");
			saveActionToIni("SavingActionTest.ini");
			saveToIni("SavingTest.ini");
			std::cout << "... Done." << std::endl;
		}
		if(check("LoadSavedIni"))
		{
			std::cout << "LoadSavedIni a ete declenche : Chargement de SavingTest.ini ..." << std::endl;
			free();
			loadFromIni("SavingTest.ini");
			saveToIni("SavingTest.ini");
			std::cout << "... Done." << std::endl;
		}
		if(check("Jump"))
			std::cout << "Jump a ete declenche" << std::endl;
		if(check("ReloadConfig"))
		{
			std::cout << "Rechargement du fichier Ini..." << std::endl;
			free();
			loadFromIni("Config.ini");
			std::cout << "... Done." << std::endl;
		}
		if(check("TestAxis")) // Le seuil a-t-il été dépassé ?
			std::cout << "TestAxis a ete declenche : " << getPosition("TestAxis") << std::endl;
	}

	free();

	return EXIT_SUCCESS;
}
