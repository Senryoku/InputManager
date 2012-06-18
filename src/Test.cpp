#include <iostream>

#include "InputManager.hpp"

using namespace InputManager;

int main(void)
{
	sf::Window W;
	W.create(sf::VideoMode(800.f, 600.f), "Pooling Test");

	sf::Joystick::update(); // Necessaire sans fenêtre, et même avec on dirait...
	loadFromIni("Config.ini");

	while(W.isOpen())
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
		if(check("GetInput"))
		{
			std::cout << "GetInput a ete declenche, appuyez sur la nouvelle touche pour GetInput2..." << std::endl;
			Input* newInput = createInput(W, "GetInput2");
			if(newInput != NULL)
				std::cout << "Done ! Nouvelle touche : " << newInput->getIniStrDesc() << std::endl;
			else std::cout << "Annulé." << std::endl;
		}
		if(check("GetInput2"))
		{
			std::cout << "GetInput2 a ete declenche !" << std::endl;
		}
		if(check("Escape")) W.close();

		W.display();
	}

	free();

	return EXIT_SUCCESS;
}
