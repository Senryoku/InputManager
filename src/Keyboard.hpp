#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "Button.hpp"

#include <SFML/Window/Keyboard.hpp>

namespace InputManager
{

class Keyboard : public Button
{
	public:
		/// @brief Constructeur
		Keyboard(const std::string& Name, sf::Keyboard::Key KeyID);
		~Keyboard();

		void update();
		std::string getIniStrDesc();

	protected:
		sf::Keyboard::Key myButtonID;

	private:
};

} // Namespace InputManager

#endif // KEYBOARD_HPP
