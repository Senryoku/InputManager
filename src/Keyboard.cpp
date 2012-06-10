#include "Keyboard.hpp"

Keyboard::Keyboard(std::string Name, sf::Keyboard::Key KeyID) :
	Button(Name), myButtonID(KeyID)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::update()
{
	bool NowPressed = sf::Keyboard::isKeyPressed(myButtonID);
	myJustPressed = (!myPressed && NowPressed);
	myJustReleased = (myPressed && !NowPressed);
	myPressed = NowPressed;
}

std::string Keyboard::getIniStrDesc()
{
	std::ostringstream SStr;
	SStr << myButtonID;
	return SStr.str();
}
