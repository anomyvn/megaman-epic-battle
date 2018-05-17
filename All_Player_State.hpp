#pragma once
#include <iostream>
#include "Player_State.hpp"
#include "player.hpp"
namespace frost
{
	class Dashing_State:public Player_State
	{
	public:
		Dashing_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};
	class Running_State :public Player_State
	{
	public:
		Running_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};
	
	
	class Jumping_State :public Player_State
	{
	public:
		Jumping_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};
	class Standing_State :public Player_State
	{
	public:
		Standing_State(Player *player_);
		Player_State* HandleInput(Key *key,int key_num);
		void Update();
	private:
		Player * player;
	};
	
	class Ducking_State :public Player_State
	{
	public:
		Ducking_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};
	class Attacking_State :public Player_State
	{
	public:
		Attacking_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};

	class Falling_State :public Player_State
	{
	public:
		Falling_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};

	class Special_Attack_State : public Player_State
	{
	public:
		Special_Attack_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};

	class Ducking_Attack_State :public Player_State
	{
	public:
		Ducking_Attack_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};

	class Ducking_Specialattack_State :public Player_State
	{
	public:
		Ducking_Specialattack_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};

	

	class Dashing_Attack_State :public Player_State
	{
	public:
		Dashing_Attack_State(Player *player_);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;
	};

	class On_air_Special_attack_State: public Player_State
	{
	public:
		On_air_Special_attack_State(Player *player);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;

	};

	class Dashing_Special_attack_State : public Player_State
	{
	public:
		Dashing_Special_attack_State(Player *player);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;

	};

	class Wall_Sliding_State : public Player_State
	{
	public:
		Wall_Sliding_State(Player *player);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;

	};
	class Second_Jump_State : public Player_State
	{
	public:
		Second_Jump_State(Player *player);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;

	};

	class Giga_Attack_State : public Player_State
	{
	public:
		Giga_Attack_State(Player *player);
		Player_State* HandleInput(Key *key, int key_num);
		void Update();
	private:
		Player * player;

	};
}