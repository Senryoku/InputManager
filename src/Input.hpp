#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include <sstream>
#include <map>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace InputManager
{

class Input
{
	public:
		/// @brief Constructeur
		Input(const std::string& Name);
		virtual ~Input();

		std::string getName() { return myName; }

		/// @brief Mise à jour de l'état de l'input suivi
		virtual void update() =0;

		virtual bool isPressed() =0;
		virtual bool wasJustPressed() =0;
		virtual bool wasJustReleased() =0;
		/// @brief Retourne la description de l'input telle qu'elle sera dans un Ini
		virtual std::string getIniStrDesc() =0;

		virtual float getPosition() =0;

		// Actions spécifiques à un type, ne font rien si appliqué au mauvais type
		inline virtual void setThreshold(float T) { }
		inline virtual void setKeyID(sf::Keyboard::Key) { }
		inline virtual void setButID(sf::Mouse::Button) { }
		inline virtual void setJoyID(unsigned int JoyID) { }
		inline virtual void setButID(unsigned int ButID) { }
		inline virtual void setAxisID(sf::Joystick::Axis) { }

		static bool isUsed(const std::string& Name);
		static Input* get(const std::string& Name);
		static void updateAll();
		static void deleteAll();
		static std::map<std::string, Input*>::iterator getIterator() { return Input::KeyMap.begin(); }
		static std::map<std::string, Input*>::iterator getItEnd() { return Input::KeyMap.end(); }

	protected:
		static std::map<std::string, Input*> KeyMap;

		std::string myName;

	private:
};

} // Namespace InputManager

#endif // _INPUT_HPP_
