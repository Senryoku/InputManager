#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Input.hpp"

class Button : public Input
{
	public:
		/// @brief Constructeur
		Button(std::string Name);
		virtual ~Button();

		/// @brief Mise à jour de l'état du boutton
		virtual void update() =0;

		/// @brief Accesseur de myPressed
		bool isPressed() { return myPressed; }
		/// @brief Accesseur de myJustPressed
		bool wasJustPressed() { return myJustPressed; }
		/// @brief Accesseur de myJustReleased
		bool wasJustReleased() { return myJustReleased; }

		float getPosition() { return 0.f; }

	protected:
		bool myPressed;			///< Vaut Vrai si le boutton est appuyé
		bool myJustPressed;		///< Vaut Vrai si le boutton vient d'être enfoncé
		bool myJustReleased;	///< Vaut Vrai si le boutton vient d'être relâché

	private:
};

#endif // _BUTTON_H_
