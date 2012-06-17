#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#include "Button.hpp"

#include <SFML/Window/Mouse.hpp>

namespace InputManager
{

class Mouse : public Button
{
	public:
		/// @brief Constructeur
		Mouse(std::string Name, sf::Mouse::Button ButID);
		~Mouse();

		void update();
		std::string getIniStrDesc();

	protected:
		sf::Mouse::Button myButtonID;

	private:
};

} // Namespace InputManager

#endif // _MOUSE_HPP_
