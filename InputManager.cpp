#pragma once

#include "InputManager.hpp"

namespace frost
{
	InputManager::InputManager()
	{
		_action1.left = sf::Keyboard::Left;
		_action1.right = sf::Keyboard::Right;
		_action1.up = sf::Keyboard::Up;
		_action1.down = sf::Keyboard::Down;
		_action1.atk = sf::Keyboard::Period;
		_action1.def = sf::Keyboard::Comma;
		_action1.mana = sf::Keyboard::Slash;

		_action2.left = sf::Keyboard::D;
		_action2.right = sf::Keyboard::A;
		_action2.up = sf::Keyboard::W;
		_action2.down = sf::Keyboard::S;
		_action2.atk = sf::Keyboard::G;
		_action2.def = sf::Keyboard::H;
		_action2.mana = sf::Keyboard::J;


	}
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect playButtonRect(object.getPosition().x,object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (playButtonRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}

		return false;
	}
	action InputManager::Getkey1()
	{
		
		
		return _action1;
	}

	action InputManager::Getkey2()
	{	
		return _action2;
	}
	bool InputManager::IsButtonClicked(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
}