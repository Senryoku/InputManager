#include "Button.hpp"

namespace InputManager
{

Button::Button(const std::string& Name) : Input(Name),
	myPressed(false), myJustPressed(false), myJustReleased(false)
{
}

Button::~Button()
{
}

void Button::reset()
{
	myPressed = false;
	myJustPressed = false;
	myJustReleased = false;
}

} // Namespace InputManager
