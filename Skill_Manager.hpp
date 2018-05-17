#pragma once
#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#define Frame_time 1.0f/20.0f
#include "Collision.hpp"
#include "player.hpp"

namespace frost
{
	struct Skill_data
	{
		sf::Vector2f pos;// position of orgin
		sf::Vector2f orgin;
		sf::Vector2f vector;
		std::string texture;
		sf::Sprite sprite;
		bool invisible=false;// for saber attack only
		bool destroyable = true;
		int player = 1;
		float damage =0.0f;
		bool effect;
		float clock;
		sf::IntRect *rect;
		int rect_num;
		int pre_framenum=0;//frame before skill 
		int framenum;
		float frame_time = Frame_time;
		bool one_animation_skill = false;
		bool avaiable = true;
	};

	class Skill
	{
	public:
		Skill(Skill_data data,GameDataRef game_data);
		Skill_data Get_Skill_data();

		void Update(float dt);
		void Draw();
	private:
		
		Skill_data data_;
		GameDataRef game_data_;
	};

	class Skill_Manager
	{
	public:
		Skill_Manager(GameDataRef data__);
		void AddSkill(Skill skill);
		void Update(float dt);
		void Add_Explosion(sf::Vector2f pos);
		void Draw();
		void Add_Player(Player *player_);
		void Skill_Hit(Player *player,sf::Sprite player_sprite);
		//void Remove();
	private:
		std::vector<Skill> skill_;
		GameDataRef data;
		Player *player;
	};
}