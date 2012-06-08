#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "Button.hpp"

#include <SFML/Window/Keyboard.hpp>

class Keyboard : public Button
{
	public:
		Keyboard(std::string Name, sf::Keyboard::Key KeyID);
		virtual ~Keyboard();

		void update();

	protected:
		sf::Keyboard::Key myButtonID;

	private:
};

#endif // KEYBOARD_HPP
