#include <iostream>

#include "Action.hpp"
#include "Input.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Joystick.hpp"

int main(void)
{
	Keyboard I("Test1", sf::Keyboard::A);
	Keyboard J("Test2", sf::Keyboard::E);
	Keyboard K("Escape1", sf::Keyboard::Escape);

	Action B("Test", Action::Pressed, "Test1", "Test2");
	Action A("Escape", Action::JustPressed, "Escape1");

	while(!Action::isValid("Escape"))
	{
		Input::updateAll();
		if(Action::isValid("Test"))
			std::cout << "Test a ete declenche" << std::endl;
	}

	return EXIT_SUCCESS;
}
