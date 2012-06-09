#include "Button.hpp"

Button::Button(std::string Name) : Input(Name),
	myPressed(false), myJustPressed(false), myJustReleased(false)
{
}

Button::~Button()
{
}
