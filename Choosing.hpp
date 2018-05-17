#pragma once
#include "SFML\Graphics.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include <string>

namespace frost
{
	class Choosing_State: public State
	{
	public:
		Choosing_State(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		float clock_1=0.0f;
		float clock_2 = 0.0f;
		GameDataRef data_;
		bool Left_1 = false;
		bool Right_1 = false;
		bool Left_2 = false;
		bool Right_2 = false;
		sf::Sprite back_ground;
		sf::Sprite choose;
		int frame_1 = 0;
		int frame_2 = 0;
		int play_1 = 0;
		int play_2 = 0;
		bool key_lock_1 = false;
		bool key_lock_2 = false;
		sf::Sprite player1,player1_1,player1_2;
		
		sf::Sprite player2,player2_1,player2_2;

		std::string name_1;
		std::string name_2;
	};
}