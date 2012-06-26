#include "Axis.hpp"

namespace InputManager
{

Axis::Axis(const std::string& Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T) :
	Input(Name), myJoystickID(JoyID), myAxisID(AxisID), myPosition(0)
{
	setThreshold(T);
}

Axis::~Axis()
{
}

void Axis::setThreshold(float T)
{
	if(T > 100.f)
		T = 100.f;
	else if(T < 0.f)
		T = 0.f;
	myThreshold = T;
}

void Axis::update()
{
	myPosition = sf::Joystick::getAxisPosition(myJoystickID, myAxisID);
	if(std::abs(myPosition) < myThreshold) myPosition = 0.f;
}

std::string Axis::getIniStrDesc()
{
	std::ostringstream SStr;
	SStr << "JoyA " << myJoystickID << " " << myAxisID;
	return SStr.str();
}

void Axis::reset()
{
	myPosition = 0.f;
}

} // Namespace InputManager
