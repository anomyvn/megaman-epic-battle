#pragma once

#include "player.hpp"
#include "HUD.hpp"
#include "SFML\Graphics.hpp"
#include "Game.hpp"
#include "All_Player_State.hpp"
#include <algorithm>
#include "Skill_Manager.hpp"
#include <string>

#define frame_size 180
#define velocityx  sf::Vector2f(300.0f, 0.0f)
#define velocityy  sf::Vector2f(0.0f, -500.0f)
#define Max_height 250.0f
#define Gravity 420.0f
#define Ceiling 240.0f
//#include "Character.hpp"
#include <iostream>
namespace frost
{
	class Character;
	class Zero: public Player
	{
	public:
		Zero(GameDataRef data__,  Key *key_,Skill_Manager *skill_manager,int player,std::string name);
		void HandleInput();
		void Update(float dt);
		void Draw();
		void Hit_State();
		sf::Sprite Get_Sprite();
		void HIT(float damage);
		void Reset();
		void Jump();
		void Second_Jump();
		void On_air_attack();
		void On_air_Special_attack();
		Status *Get_status();
		Key_lock Get_Key_lock();
		void Update_key_lock();
		void Giga_Attack();
		void Run();
		void Attack();
		void Attack_1();
		void Attack_2();
		void Rut_Kiem();
		void Dash();
		void Duck();
		void Stand();
		void Fall();
		void Special_Attack();
		void Duck_Attack();
		void Duck_Special_Attack();
		void Dash_Attack();
		void Dash_Special_Attack();
		void Wall_slide();
		
	private:
		Status status;
		Player_State *player_state;
		sf::Sprite sprite;
		GameDataRef data;
		Player *player;
		bool keylock;// lock all input
		int framenum;
		int framenum_air_attack;//diff from regular framenum
		float clock;
		float clock1;
		int direct;//hướng của sprite
		sf::Vector2f velocity_x,velocity_y;
		float dt_;
		bool air_attack;
		bool using_skill;//put a skil at a time
		bool change_attribute_hold;
		bool on_air;
		bool sliding;
		bool second_jump;
		int key_num;
		int last_frame_attack;// for saber attack
		Key *key;
		float time;//tinh v
		Skill_Manager *skill_manager_;

		bool invisible; // take no damage
		bool hit = false; // true if being hit
		float hit_time=0.0f;// time being invisible
		

		float set_off;// to end dashing
		float set_off_y; // to end second jump
		bool second_jump_avaiable;
		int last_direct;// to end dashing
		int circle = 0;
		Key_lock key_lock;

		sf::Sprite Giga_sprite;
		sf::IntRect Giga_frame[70];
		sf::Sprite Maverick_Zero_1;
		sf::Sprite Maverick_Zero_2;
		bool maverick_zero_mode = false;
		float clock_maverick=0.0f;
		int maverick_framenum=0.0f;

		bool giga_effect;
		sf::Sprite sprite_;//to check collision
	};
}
