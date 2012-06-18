#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

/* *****************************************
 * Simple InputManager
 *
 * By Senryoku <maretverdant@gmail.com>
 *
 * Lastest version can be found here :
 * https://github.com/Senryoku/InputManager
 * *****************************************/

#include <sstream>
#include <SFML/Window.hpp>

#include "Input.hpp"
#include "Button.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Joystick.hpp"
#include "Axis.hpp"
#include "Action.hpp"

#include "SimpleIniParser/IniFile.hpp"

namespace InputManager
{

	/** @brief Charge une configuration (d'input) depuis un fichier Ini
	 *
	 * Format :
	 * Label = 42
	 * Où 42 est un numero de touche (SFML)
	 * Label = Mouse 0
	 * Désigne le bouton 0 (Gauche) de la souris
	 * Label = Joy 0 1
	 * Désigne le bouton 1 du Joystick 0
	 * Label = JoyA 0 1
	 * Désigne l'axe 1 du Joystick 0
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser, valeur par défaut : "Input"
	 * @return true si le chargement s'est bien déroulé
	**/
	bool loadInputFromIni(const std::string& Path,const std::string& Name = "Input");

	/** @brief Charge une liste d'Actions depuis un fichier Ini
	 *
	 * Format :
	 * Label = Action::Type InputLabel1 InputLabel2
	 * Exemple :
	 * Jump = 1 Jump1 Jump2
	 * InputLabel2 est facultatif, les espaces sont utilisés comme
	 * séparateurs dans la Value (la partie droite), ils sont ignorés
	 * ailleurs. Action::Type est défini dans Action.
	 * Si les InputLabel ne sont pas prédéfinis, l'Action sera créée
	 * mais sera toujours fausse (puisse qu'elle n'aura pas d'input à tester).
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser valeur par défaut : "Action"
	 * @return true si le chargement s'est bien déroulé
	**/
	bool loadActionFromIni(const std::string& Path, const std::string& Name = "Action");

	bool loadFromIni(const std::string& Path, const std::string& InputSection = "Input", const std::string& ActionSection = "Action");

	/** @brief Sauvegarde les Input dans un fichier Ini
	 *
	 * /!\ Remplacera complètement le fichier cible !
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser valeur par défaut : "Input"
	 * @return true si la sauvegarde s'est bien déroulée
	**/
	bool saveInputToIni(const std::string& Path, const std::string& Name = "Input");

	/** @brief Sauvegarde les Actions dans un fichier Ini
	 *
	 * /!\ Remplacera complètement le fichier cible !
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser valeur par défaut : "Action"
	 * @return true si la sauvegarde s'est bien déroulée
	**/
	bool saveActionToIni(const std::string& Path, const std::string& Name = "Action");

	/** @brief Sauvegarde les Inputs et les Actions dans un unique fichier Ini
	 *
	 * /!\ Remplacera complètement le fichier cible !
	 * @param Path Chemin vers le fichier
	 * @param Name Section à utiliser pour les Inputs valeur par défaut : "Input"
	 * @param Name Section à utiliser pour les Actions valeur par défaut : "Action"
	 * @return true si la sauvegarde s'est bien déroulée
	**/
	bool saveToIni(const std::string& Path, const std::string& InputSection = "Input", const std::string& ActionSection = "Action");

	/** @brief Modifie le seuil de tout les axes surveillés
	**/
	void setGlobalThreshold(float T);

	/** @brief Ajoute un Input à surveiller (Keyboard)
	 *
	 * @param Name Identifiant (std::string)
	 * @param KeyID Identifiant SFML de la touche à surveiller
	 * @return Pointeur vers l'Input (Keyboard) créé
	**/
	Keyboard* add(const std::string& Name, sf::Keyboard::Key KeyID);

	/** @brief Ajoute un Input à surveiller (Mouse)
	 *
	 * @param Name Identifiant (std::string)
	 * @param ButID Identifiant SFML du bouton souris à surveiller
	 * @return Pointeur vers l'Input (Mouse) créé
	**/
	Mouse* add(const std::string& Name, sf::Mouse::Button ButID);

	/** @brief Ajoute un Input à surveiller (Joystick)
	 *
	 * @param Name Identifiant (std::string)
	 * @param JoyID Identifiant SFML du Joystick
	 * @param ButID Identifiant SFML du boutton à surveiller
	 * @return Pointeur vers l'Input (Joystick) créé
	**/
	Joystick* add(const std::string& Name, unsigned int JoyID, unsigned int ButID);

	/** @brief Ajoute un Input à surveiller (Axis)
	 *
	 * @param Name Identifiant (std::string)
	 * @param JoyID Identifiant SFML du Joystick
	 * @param AxisID Identifiant SFML de l'axe à surveiller
	 * @return Pointeur vers l'Input (Axis) créé
	**/
	Axis* add(const std::string& Name, unsigned int JoyID, sf::Joystick::Axis AxisID, float T = 10.f);

	/** @brief Ajoute une Action
	 *
	 * @param ActionName Identifiant (std::string)
	 * @param Type Type d'action
	 * @param I1 Input déclenchant l'action
	 * @param I2 Input déclenchant l'action
	 * @return Pointeur vers l'Action créée
	**/
	Action* add(const std::string& ActionName, Action::Type Type, Input* I1 = NULL, Input* I2 = NULL);

	/** @brief Ajoute une Action
	 *
	 * @param ActionName Identifiant (std::string)
	 * @param Type Type d'action
	 * @param I1 Identifiant d'Input déclenchant l'action
	 * @param I2 Identifiant d'Input déclenchant l'action
	 * @return Pointeur vers l'Action créée
	**/
	Action* add(const std::string& ActionName, Action::Type Type, std::string I1 = "", std::string I2 = "");

	/** @brief Retourne l'état courant de l'Action demandée
	 *
	 * Dans le cas d'une Action de Type Axis, retournera vrai
	 * si le seuil de déclenchement a été dépassé.
	 * @param ActionName Identifiant d'une Action
	 * @return Etat courant de l'action demandée
	**/
	bool check(const std::string& ActionName);

	/** @brief Retourne l'état courant de l'Action (Type Axis) demandée
	 *
	 * @param ActionName Identifiant d'une Action (Type Axis)
	 * @return Etat courant de l'action demandée
	**/
	float getPosition(const std::string& ActionName);

	/** @brief Effectue les mises à jour des Input
	**/
	void update();

	/** @brief Libère tout les Inputs/Actions
	**/
	void free();

	/** @brief Créé et retourne un pointeur vers un Input
	 * surveillant la prochaine touche appuyée (Event SFML)
	 *
	 * @param W sf::Window
	 * @param Name Identifiant de l'Input créé
	 * @return NULL si Escape est appuyée, Input* sinon
	**/
	Input* createInput(sf::Window& W, const std::string& Name);

} // Namespace InputManager

#endif // _INPUTMANAGER_HPP_
