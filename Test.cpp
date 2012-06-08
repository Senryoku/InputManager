#include <iostream>

#include "InputManager.hpp"

int main(void)
{
	InputManager IM;

	IM.add("Test1", sf::Keyboard::A);
	IM.add("Test2", sf::Keyboard::E);
	IM.add("Test3", sf::Keyboard::R);
	IM.add("Test3445", sf::Keyboard::R);
	IM.add("Escape1", sf::Keyboard::Escape);

	InputManager::add("TestMouse", sf::Mouse::Left);

	Axis Ax("Move", 0, sf::Joystick::X, 15.f);

	Joystick Joy1("Jump", 0, 0);

	Action B("Test", Action::Pressed, "Test1", "Test2");
	Action A("Escape", Action::JustPressed, "Escape1");
	Action C("TestJust", Action::JustPressed, "Test3");
	Action D("TestJustR", Action::JustReleased, "Test3");
	Action G("TestMouse", Action::JustReleased, "TestMouse");
	Action F("TestAxis", Action::Axis, "Move");
	Action Jump("Jump", Action::JustPressed, "Jump");

	while(!Action::check("Escape"))
	{
		sf::Joystick::update();
		Input::updateAll();
		if(Action::check("Test"))
			std::cout << "Test a ete declenche" << std::endl;
		if(Action::check("TestJust"))
			std::cout << "TestJust a ete declenche" << std::endl;
		if(Action::check("TestJustR"))
			std::cout << "TestJustR a ete declenche" << std::endl;
		if(Action::check("TestMouse"))
			std::cout << "TestMouse a ete declenche" << std::endl;
		if(Action::check("Jump"))
			std::cout << "Jump a ete declenche" << std::endl;
		if(abs(Action::getPosition("TestAxis")) != 0.f)
			std::cout << "TestAxis a ete declenche : " << Action::getPosition("TestAxis") << std::endl;
	}

	return EXIT_SUCCESS;
}
