#include "Mouse.hpp"

namespace InputManager
{

Mouse::Mouse(std::string Name, sf::Mouse::Button ButID) :
	Button(Name), myButtonID(ButID)
{
}

Mouse::~Mouse()
{
}

void Mouse::update()
{
	bool NowPressed = sf::Mouse::isButtonPressed(myButtonID);
	myJustPressed = (!myPressed && NowPressed);
	myJustReleased = (myPressed && !NowPressed);
	myPressed = NowPressed;
}

std::string Mouse::getIniStrDesc()
{
	std::ostringstream SStr;
	SStr << "Mouse " << myButtonID;
	return SStr.str();
}

} // Namespace InputManager
