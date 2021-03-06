#ifndef _AXIS_HPP_
#define _AXIS_HPP_

#include <cmath>

#include "Input.hpp"

#include <SFML/Window/Joystick.hpp>

namespace InputManager
{

class Axis : public Input
{
	public:
		/// @brief Constructeur
		Axis(const std::string& Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T = 10.f);
		~Axis();

		void setThreshold(float T);
		inline void setJoyID(unsigned int JoyID) { myJoystickID = JoyID; }
		inline void setAxisID(sf::Joystick::Axis A) { myAxisID = A; }

		// N'est pas sensé être utilisé avec un Axis
		// Retournera vrai si le seuil est dépassé
		bool isPressed() { return static_cast<bool>(myPosition); }
		bool wasJustPressed() { return false; }
		bool wasJustReleased() { return false; }

		float getPosition() { return myPosition; }

		void update();
		void reset();
		std::string getIniStrDesc();

	protected:
		unsigned int myJoystickID; ///< Identifiant SFML du Joystick
		sf::Joystick::Axis myAxisID; ///< Identifiant SFML de l'axe surveillé

		float myPosition; ///< Valeur courante de l'axe (modulé par le seuil)
		float myThreshold; ///< Valeur (absolue) minimale pour la mise à jour de myPosition

	private:
};

} // Namespace InputManager

#endif // _AXIS_HPP_
