#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "Button.hpp"

#include <SFML/Window/Mouse.hpp>

class Mouse : public Button
{
	public:
		/// @brief Constructeur
		Mouse(std::string Name, sf::Mouse::Button ButID);
		~Mouse();

		void update();

	protected:
		sf::Mouse::Button myButtonID;

	private:
};

#endif // _MOUSE_HPP_
