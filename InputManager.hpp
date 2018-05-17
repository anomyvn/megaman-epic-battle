#pragma once

#include "SFML\Graphics.hpp"

namespace frost
{
	struct action
	{
		sf::Keyboard::Key left, right, up, down, atk, def, mana;
	};
	class InputManager
	{
	public:
		InputManager();
		~InputManager() {}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
		bool IsButtonClicked(sf::Keyboard::Key key);
		action Getkey1();
		action Getkey2();
	private:
		action _action1;
		action _action2;
		;
	};
}