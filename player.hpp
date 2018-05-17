#pragma once
#define Ground 700.0f
#include "Collision.hpp"

namespace frost
{
	enum  Attribute
	{
		neutral,fire,lightning,ice
	};

	enum Type
	{
		zero,x
	};
	struct Status
	{
		float Health;
		float Max_Health;
		float Mana;
		float Max_Mana;
		float Attack;
		float Def;
		Attribute attribute;
		Type type;
		int player_num;
	};

	struct Key_lock
	{
		float attack_lock=0.0f;
		float dash_lock=0.0f;
		float jump_lock=0.0f;
		float special_lock = 0.0f;
		float left_lock = 0.0f;
		float right_lock = 0.0f;

	};
	class Player
	{
	public: 
		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;

		virtual Status *Get_status() = 0;
		virtual void HIT(float damage) = 0;
		virtual void Jump() = 0;
		virtual void Run() = 0;
		virtual void Attack() = 0;
		virtual void Dash() = 0;
		virtual void Duck() = 0;
		virtual void Stand() = 0;
		virtual void Reset() = 0;
		virtual void Fall() = 0;
		virtual void Special_Attack() = 0;
		virtual void Duck_Attack() = 0;
		virtual void Duck_Special_Attack() = 0;
		virtual void Dash_Attack() = 0;
		virtual void Dash_Special_Attack() = 0;
		virtual void On_air_Special_attack() = 0;
		virtual void Wall_slide() = 0;
		virtual Key_lock Get_Key_lock() = 0;
		virtual void Second_Jump() = 0;
		virtual void Giga_Attack() = 0;
		virtual sf::Sprite Get_Sprite() = 0;

	};
}
