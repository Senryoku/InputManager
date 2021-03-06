#include "Joystick.hpp"

namespace InputManager
{

Joystick::Joystick(const std::string& Name, unsigned int JoyID, unsigned int ButID) :
	Button(Name), myJoystickID(JoyID), myButtonID(ButID)
{
}

Joystick::~Joystick()
{
}

void Joystick::update()
{
	bool NowPressed = sf::Joystick::isButtonPressed(myJoystickID, myButtonID);
	myJustPressed = (!myPressed && NowPressed);
	myJustReleased = (myPressed && !NowPressed);
	myPressed = NowPressed;
}

std::string Joystick::getIniStrDesc()
{
	std::ostringstream SStr;
	SStr << "Joy " << myJoystickID << " " << myButtonID;
	return SStr.str();
}

} // Namespace InputManager
