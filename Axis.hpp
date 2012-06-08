#ifndef _AXIS_HPP_
#define _AXIS_HPP_

#include "Input.hpp"

#include <SFML/Window/Joystick.hpp>

class Axis : public Input
{
	public:
		Axis(std::string Name, unsigned int JoyID, sf::Joystick::Axis AxisID);
		~Axis();

		bool isPressed() { return false; }
		bool wasJustPressed() { return false; }
		bool wasJustReleased() { return false; }

		float getPosition() { return myPosition; }

		void update();

	protected:
		unsigned int myJoystickID;
		sf::Joystick::Axis myAxisID;

		float myPosition;

	private:
};

#endif // _AXIS_HPP_
