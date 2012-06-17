#ifndef _ACTION_HPP_
#define _ACTION_HPP_

#include <map>
#include <string>

#include "Input.hpp"

namespace InputManager
{

class Action
{
	public:
		enum Type {
			Pressed, 		///< check() renvera Vrai si la touche est appuyée
			JustPressed, 	///< check() renvera Vrai si la touche vient d'être enfoncée
			JustReleased,	///< check() renvera Vrai si la touche vient d'être relâchée
			Axis			///< getPosition() renvera la position d'un axe
		};

		/// @brief Constructeur
		Action(const std::string ActionName, Type Type, Input* I1 = NULL, Input* I2 = NULL);
		/// @brief Constructeur
		Action(const std::string ActionName, Type Type, const std::string I1 = "", const std::string I2 = "");
		virtual ~Action();

		Type getType() { return myType; }

		Input* getInput1() { return myInput1; }
		Input* getInput2() { return myInput2; }

		void setInput(std::string InputName, unsigned int Number = 0);
		void setInput(Input* I, unsigned int Number = 0);

		void addInput(std::string InputName);
		void addInput(Input* I);

		bool check();
		float getPosition();

		static bool check(const std::string ActionName);
		static float getPosition(const std::string ActionName);

		static bool exists(const std::string ActionName) { return Map.count(ActionName); }
		static Action* get(const std::string ActionName);
		static std::map<std::string, Action*>::iterator getIterator() { return Action::Map.begin(); }
		static std::map<std::string, Action*>::iterator getItEnd() { return Action::Map.end(); }

		static void deleteAll();

	protected:
		static std::map<std::string, Action*> Map;

		std::string myName;

		Input* myInput1;
		Input* myInput2;

		Type myType;

	private:
};

} // Namespace InputManager

#endif // _ACTION_HPP_
