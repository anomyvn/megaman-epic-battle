#pragma once
#include "Input.hpp"
#include "SFML\Graphics.hpp"
#include "player.hpp"
namespace frost
{
	class Player_State
	{
	public:
		virtual Player_State* HandleInput(Key *key, int key_num) = 0;
		virtual void Update() = 0;

		
	};
}