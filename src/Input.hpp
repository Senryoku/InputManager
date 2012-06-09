#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include <map>
#include <string>
#include <SFML/System.hpp>

class Input
{
	public:
		/// @brief Constructeur
		Input(std::string Name);
		virtual ~Input();

		std::string getName() { return myName; }

		/// @brief Mise à jour de l'état de l'input suivi
		virtual void update() =0;

		virtual bool isPressed() =0;
		virtual bool wasJustPressed() =0;
		virtual bool wasJustReleased() =0;

		virtual float getPosition() =0;

		static bool isUsed(std::string Name);
		static Input* get(std::string Name);
		static void updateAll();
		static void deleteAll();

	protected:
		static std::map<std::string, Input*> KeyMap;

		std::string myName;

	private:
};

#endif // _INPUT_HPP_
