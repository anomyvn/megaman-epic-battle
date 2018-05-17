#pragma once
#include "Game.hpp"
#include "State.hpp"
#include "SFML\Graphics.hpp"
#include <string>
#include "Choosing.hpp"
namespace frost
{
	class Gameover_State : public State
	{
	public:
		Gameover_State(GameDataRef data,std::string text);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef data_;
		sf::Text text_;
		float clock = 0.0f;
	};
}