#include "Keyboard.hpp"

std::string convertKeytoStr(sf::Keyboard::Key K);

Keyboard::Keyboard(std::string Name, sf::Keyboard::Key KeyID) :
	Button(Name), myButtonID(KeyID)
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::update()
{
	bool NowPressed = sf::Keyboard::isKeyPressed(myButtonID);
	myJustPressed = (!myPressed && NowPressed);
	myJustReleased = (myPressed && !NowPressed);
	myPressed = NowPressed;
}

std::string Keyboard::getIniStrDesc()
{
	// Version utilisant l'identifiant entier
//	std::ostringstream SStr;
//	SStr << myButtonID;
//	return SStr.str();
	// Vertsion utilisant une chaîne de caractère
	return convertKeytoStr(myButtonID);
}

std::string convertKeytoStr(sf::Keyboard::Key K)
{
	if(K == sf::Keyboard::A) return "A";
	if(K == sf::Keyboard::B) return "B";
	if(K == sf::Keyboard::C) return "C";
	if(K == sf::Keyboard::D) return "D";
	if(K == sf::Keyboard::E) return "E";
	if(K == sf::Keyboard::F) return "F";
	if(K == sf::Keyboard::G) return "G";
	if(K == sf::Keyboard::H) return "H";
	if(K == sf::Keyboard::I) return "I";
	if(K == sf::Keyboard::J) return "J";
	if(K == sf::Keyboard::K) return "K";
	if(K == sf::Keyboard::L) return "L";
	if(K == sf::Keyboard::M) return "M";
	if(K == sf::Keyboard::N) return "N";
	if(K == sf::Keyboard::O) return "O";
	if(K == sf::Keyboard::P) return "P";
	if(K == sf::Keyboard::Q) return "Q";
	if(K == sf::Keyboard::R) return "R";
	if(K == sf::Keyboard::S) return "S";
	if(K == sf::Keyboard::T) return "T";
	if(K == sf::Keyboard::U) return "U";
	if(K == sf::Keyboard::V) return "V";
	if(K == sf::Keyboard::W) return "W";
	if(K == sf::Keyboard::X) return "X";
	if(K == sf::Keyboard::Y) return "Y";
	if(K == sf::Keyboard::Z) return "Z";
	if(K == sf::Keyboard::Num0) return "Num0";
	if(K == sf::Keyboard::Num1) return "Num1";
	if(K == sf::Keyboard::Num2) return "Num2";
	if(K == sf::Keyboard::Num3) return "Num3";
	if(K == sf::Keyboard::Num4) return "Num4";
	if(K == sf::Keyboard::Num5) return "Num5";
	if(K == sf::Keyboard::Num6) return "Num6";
	if(K == sf::Keyboard::Num7) return "Num7";
	if(K == sf::Keyboard::Num8) return "Num8";
	if(K == sf::Keyboard::Num9) return "Num9";
	if(K == sf::Keyboard::Escape) return "Escape";
	if(K == sf::Keyboard::LControl) return "LControl";
	if(K == sf::Keyboard::LShift) return "LShift";
	if(K == sf::Keyboard::LAlt) return "LAlt";
	if(K == sf::Keyboard::LSystem) return "LSystem";
	if(K == sf::Keyboard::RControl) return "RControl";
	if(K == sf::Keyboard::RShift) return "RShift";
	if(K == sf::Keyboard::RAlt) return "RAlt";
	if(K == sf::Keyboard::RSystem) return "RSystem";
	if(K == sf::Keyboard::Menu) return "Menu";
	if(K == sf::Keyboard::LBracket) return "LBracket";
	if(K == sf::Keyboard::RBracket) return "RBracket";
	if(K == sf::Keyboard::SemiColon) return "SemiColon";
	if(K == sf::Keyboard::Comma) return "Comma";
	if(K == sf::Keyboard::Period) return "Period";
	if(K == sf::Keyboard::Quote) return "Quote";
	if(K == sf::Keyboard::Slash) return "Slash";
	if(K == sf::Keyboard::BackSlash) return "BackSlash";
	if(K == sf::Keyboard::Tilde) return "Tilde";
	if(K == sf::Keyboard::Equal) return "Equal";
	if(K == sf::Keyboard::Dash) return "Dash";
	if(K == sf::Keyboard::Space) return "Space";
	if(K == sf::Keyboard::Return) return "Return";
	if(K == sf::Keyboard::Back) return "Back";
	if(K == sf::Keyboard::Tab) return "Tab";
	if(K == sf::Keyboard::PageUp) return "PageUp";
	if(K == sf::Keyboard::PageDown) return "PageDown";
	if(K == sf::Keyboard::End) return "End";
	if(K == sf::Keyboard::Home) return "Home";
	if(K == sf::Keyboard::Insert) return "Insert";
	if(K == sf::Keyboard::Delete) return "Delete";
	if(K == sf::Keyboard::Add) return "Add";
	if(K == sf::Keyboard::Subtract) return "Subtract";
	if(K == sf::Keyboard::Multiply) return "Multiply";
	if(K == sf::Keyboard::Divide) return "Divide";
	if(K == sf::Keyboard::Left) return "Left";
	if(K == sf::Keyboard::Right) return "Right";
	if(K == sf::Keyboard::Up) return "Up";
	if(K == sf::Keyboard::Down) return "Down";
	if(K == sf::Keyboard::Numpad0) return "Numpad0";
	if(K == sf::Keyboard::Numpad1) return "Numpad1";
	if(K == sf::Keyboard::Numpad2) return "Numpad2";
	if(K == sf::Keyboard::Numpad3) return "Numpad3";
	if(K == sf::Keyboard::Numpad4) return "Numpad4";
	if(K == sf::Keyboard::Numpad5) return "Numpad5";
	if(K == sf::Keyboard::Numpad6) return "Numpad6";
	if(K == sf::Keyboard::Numpad7) return "Numpad7";
	if(K == sf::Keyboard::Numpad8) return "Numpad8";
	if(K == sf::Keyboard::Numpad9) return "Numpad9";
	if(K == sf::Keyboard::F1) return "F1";
	if(K == sf::Keyboard::F2) return "F2";
	if(K == sf::Keyboard::F3) return "F3";
	if(K == sf::Keyboard::F4) return "F4";
	if(K == sf::Keyboard::F5) return "F5";
	if(K == sf::Keyboard::F6) return "F6";
	if(K == sf::Keyboard::F7) return "F7";
	if(K == sf::Keyboard::F8) return "F8";
	if(K == sf::Keyboard::F9) return "F9";
	if(K == sf::Keyboard::F10) return "F10";
	if(K == sf::Keyboard::F11) return "F11";
	if(K == sf::Keyboard::F12) return "F12";
	if(K == sf::Keyboard::F13) return "F13";
	if(K == sf::Keyboard::F14) return "F14";
	if(K == sf::Keyboard::F15) return "F15";
	if(K == sf::Keyboard::Pause) return "Pause";
	return "Error";
}
