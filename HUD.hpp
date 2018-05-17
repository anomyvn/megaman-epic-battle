#pragma once
#include "player.hpp"
#include "Game.hpp"
#include <iostream>
#include <map>

#define speed sf::Vector2f(30.0f,0.0f)
namespace frost
{
	class HUD
	{
	public:
		HUD();
		void Setup(Status *status,GameDataRef data,int player);
		void Update(float dt);
		void Draw();
	private:
		Status * status_;
		int player_;
		GameDataRef data_;
		sf::Sprite sprite;
		sf::Sprite attr;
		sf::RectangleShape health_bar;
		sf::RectangleShape health_bar_1;
	};
}