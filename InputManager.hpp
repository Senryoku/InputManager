#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

#include "Input.hpp"
#include "Button.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Joystick.hpp"
#include "Axis.hpp"
#include "Action.hpp"

class InputManager
{
	public:
		InputManager();
		InputManager(std::string Path);
		~InputManager();

		/** @brief Charge une configuration depuis un fichier Ini
		 *
		 * @param Path Chemin vers le fichier
		 * @return true si le chargement s'est bien déroulé
		**/
		static bool loadFromIni(std::string Path);

		static Keyboard* add(std::string Name, sf::Keyboard::Key KeyID);
		static Mouse* add(std::string Name, sf::Mouse::Button ButID);
		static Joystick* add(std::string Name, unsigned int JoyID, unsigned int ButID);
		static Axis* add(std::string Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T = 10.f);
		static Action* add(const std::string ActionName, Action::Type Type, Input* I1 = NULL, Input* I2 = NULL);

		static bool check(const std::string ActionName);
		static float getPosition(const std::string ActionName);
	protected:
		static std::string myLoadedFile;
	private:
};

#endif // _INPUTMANAGER_HPP_
