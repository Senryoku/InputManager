#ifndef _ACTION_HPP_
#define _ACTION_HPP_

#include <map>
#include <string>

#include "Input.hpp"

class Action
{
	public:
		enum ActionType {
			Pressed,
			JustPressed,
			JustReleased,
			Axis
		};

		Action(const std::string ActionName, ActionType Type, Input* I1 = NULL, Input* I2 = NULL);
		Action(const std::string ActionName, ActionType Type, const std::string I1 = "", const std::string I2 = "");
		virtual ~Action();

		void addInput(std::string InputName);
		void addInput(Input* I);

		bool isValid();
		float getPosition();

		static bool isValid(const std::string ActionName);
		static float getPosition(const std::string ActionName);

	protected:
		static std::map<std::string, Action*> ActionMap;

		std::string myName;

		Input* myInput1;
		Input* myInput2;

		ActionType myType;

	private:
};

#endif // _ACTION_HPP_
