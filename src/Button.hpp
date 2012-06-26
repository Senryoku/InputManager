#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Input.hpp"

namespace InputManager
{

class Button : public Input
{
	public:
		/// @brief Constructeur
		Button(const std::string& Name);
		virtual ~Button();

		/// @brief Mise à jour de l'état du boutton
		virtual void update() =0;
		virtual void reset();

		virtual std::string getIniStrDesc() =0;

		/// @brief Accesseur de myPressed
		bool isPressed() { return myPressed; }
		/// @brief Accesseur de myJustPressed
		bool wasJustPressed() { return myJustPressed; }
		/// @brief Accesseur de myJustReleased
		bool wasJustReleased() { return myJustReleased; }

		// N'est pas sensé être utilisé avec un Button
		// Retournera 100.f si appuyé, 0.f sinon
		float getPosition() { return myPressed*100.f; }

	protected:
		bool myPressed;			///< Vaut Vrai si le boutton est appuyé
		bool myJustPressed;		///< Vaut Vrai si le boutton vient d'être enfoncé
		bool myJustReleased;	///< Vaut Vrai si le boutton vient d'être relâché

	private:
};

} // Namespace InputManager

#endif // _BUTTON_H_
