#ifndef _JOYSTICK_HPP_
#define _JOYSTICK_HPP_

#include "Button.hpp"

#include <SFML/Window/Joystick.hpp>

namespace InputManager
{

class Joystick : public Button
{
	public:
		/// @brief Constructeur
		Joystick(const std::string& Name, unsigned int JoyID, unsigned int ButID);
		~Joystick();

		void update();
		std::string getIniStrDesc();

		inline void setJoyID(unsigned int JoyID) { myJoystickID = JoyID; }
		inline void setButID(unsigned int ButID) { myButtonID = ButID; }

	protected:
		unsigned int myJoystickID;
		unsigned int myButtonID;

	private:
};

} // Namespace InputManager

#endif // _JOYSTICK_HPP_
