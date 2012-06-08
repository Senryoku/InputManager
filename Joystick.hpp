#ifndef _JOYSTICK_HPP_
#define _JOYSTICK_HPP_

#include "Button.hpp"

#include <SFML/Window/Joystick.hpp>

class Joystick : public Button
{
	public:
		Joystick(std::string Name, unsigned int JoyID, unsigned int ButID);
		virtual ~Joystick();

		void update();

	protected:
		unsigned int myJoystickID;
		unsigned int myButtonID;

	private:
};

#endif // _JOYSTICK_HPP_
