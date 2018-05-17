// the most vital part of the game, control all  most everything in game state
#pragma once
#include "player.hpp"
#include "zero.hpp"
#include <iostream>
#include "Game.hpp"
#include "Input.hpp"
#include "Skill_Manager.hpp"
#include "megaman.hpp"
#include <string>
#include "Gameover_State.hpp"
namespace frost
{
	class Character
	{
	public:
		void SetupTexture();
		bool End();
		void Init(GameDataRef data__,std::string name_1,std::string name_2);
		void HandleInput();
		void Update(float dt);
		void Draw();
		void SetUpKeyMapping();
		Player *GetPlayer_1();
		Player *GetPlayer_2();
		
	private:
		bool ending = false;
		Player * player_1;
		Player *player_2;
		HUD hud_1;
		HUD hud_2;
		GameDataRef data;
		Key key[3];
		Skill_Manager *skill_manager;

		
	};
}