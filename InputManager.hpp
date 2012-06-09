#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

#include <sstream>

#include "Input.hpp"
#include "Button.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Joystick.hpp"
#include "Axis.hpp"
#include "Action.hpp"

#include "../SimpleIniParser/IniFile.hpp"

namespace InputManager
{
	/** @brief Charge une configuration (d'input) depuis un fichier Ini
	 *
	 * Format :
	 * Label = 42
	 * Où 42 est un numero de touche (SFML)
	 * Label = Mouse 0
	 * Désigne le bouton 0 (Gauche) de la souris
	 * Label = Joy 0 1
	 * Désigne le bouton 1 du Joystick 0
	 * Label = JoyA 0 1
	 * Désigne l'axe 1 du Joystick 0
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser
	 * @return true si le chargement s'est bien déroulé
	**/
	bool loadFromIni(std::string Path, std::string Name);

	/** @brief Charge une liste d'Actions depuis un fichier Ini
	 *
	 * Format :
	 * Label = Action::Type InputLabel1 InputLabel2
	 * Exemple :
	 * Jump = 1 Jump1 Jump2
	 * InputLabel2 est facultatif, les espaces sont utilisés comme
	 * séparateurs dans la Value (la partie droite), ils sont ignorés
	 * ailleurs. Action::Type est défini dans Action.
	 * Si les InputLabel ne sont pas prédéfinis, l'Action sera créée
	 * mais sera toujours fausse (puisse qu'elle n'aura pas d'input à tester).
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser
	 * @return true si le chargement s'est bien déroulé
	**/
	bool loadActionFromIni(std::string Path, std::string Name);

	Keyboard* add(std::string Name, sf::Keyboard::Key KeyID);
	Mouse* add(std::string Name, sf::Mouse::Button ButID);
	Joystick* add(std::string Name, unsigned int JoyID, unsigned int ButID);
	Axis* add(std::string Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T = 10.f);
	Action* add(const std::string ActionName, Action::Type Type, Input* I1 = NULL, Input* I2 = NULL);
	Action* add(const std::string ActionName, Action::Type Type, std::string I1 = "", std::string I2 = "");

	bool check(const std::string ActionName);
	float getPosition(const std::string ActionName);

	void reset();
}

#endif // _INPUTMANAGER_HPP_
