#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Input.hpp"

class Button : public Input
{
	public:
		Button(std::string Name);
		virtual ~Button();

		virtual void update() =0;

		bool isPressed() { return myPressed; }
		bool wasJustPressed() { return myJustPressed; }
		bool wasJustReleased() { return myJustReleased; }

		float getPosition() { return 0.f; }

	protected:
		bool myPressed;
		bool myJustPressed;
		bool myJustReleased;

	private:
};

#endif // _BUTTON_H_
