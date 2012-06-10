#include "Axis.hpp"

Axis::Axis(std::string Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T) :
	Input(Name), myJoystickID(JoyID), myAxisID(AxisID), myPosition(0), myThreshold(abs(T))
{
}

Axis::~Axis()
{
}

void Axis::update()
{
	myPosition = sf::Joystick::getAxisPosition(myJoystickID, myAxisID);
	if(abs(myPosition) < myThreshold) myPosition = 0.f;
}

std::string Axis::getIniStrDesc()
{
	std::ostringstream SStr;
	SStr << "JoyA " << myJoystickID << " " << myAxisID;
	return SStr.str();
}
