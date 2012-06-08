#include "Axis.hpp"

Axis::Axis(std::string Name, unsigned int JoyID, sf::Joystick::Axis AxisID) :
	Input(Name), myJoystickID(JoyID), myAxisID(AxisID), myPosition(0)
{
}

Axis::~Axis()
{
}

void Axis::update()
{
	myPosition = sf::Joystick::getAxisPosition(myJoystickID, myAxisID);
}
