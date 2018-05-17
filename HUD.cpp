#include "HUD.hpp"

namespace frost
{
	HUD::HUD()
	{

	}
	void HUD::Setup(Status *status, GameDataRef data, int player) 
	{
		status_ = (status); data_ = (data); player_ = (player);
		data_->assets.LoadTexture("HUD", "Resources/res/HUD.png");
		sprite.setTexture(data->assets.GetTexture("HUD"));
		health_bar.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 255.0f));
		health_bar_1.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, 255.0f));
		attr.setTexture(data->assets.GetTexture("HUD"));
		if (player_ == 1)
		{
			sprite.setTextureRect(sf::IntRect(0, 40, 525, 90));
			
			attr.setPosition(35.0f, 45.0f);

		}
		else
		{
			sprite.setTextureRect(sf::IntRect(0, 240, 525, 90));
			sprite.setPosition(sf::Vector2f(1368.0f-sprite.getGlobalBounds().width,0.0f));
			attr.setPosition(1300.0f, 45.0f);
		}
		
	}
	void HUD::Draw()
	{
		data_->window.draw(sprite);
		data_->window.draw(attr);
		data_->window.draw(health_bar);
		data_->window.draw(health_bar_1);
	}
	void  HUD::Update(float dt)
	{
		
		
		if ((*status_).attribute == neutral) attr.setTextureRect(sf::IntRect(0, 0, 28, 30));
		if ((*status_).attribute == lightning) attr.setTextureRect(sf::IntRect(30, 0, 28, 30));
		if ((*status_).attribute == ice) attr.setTextureRect(sf::IntRect(30*2, 0, 28, 30));
		if ((*status_).attribute == fire) attr.setTextureRect(sf::IntRect(30*3, 0, 28, 30));

		//if ((*status_).Health == 0.0f) return;

		
		float length = 432.0f*(1.0f - (*status_).Health / (*status_).Max_Health);
		float length_1 = health_bar_1.getSize().x + dt * speed.x;
		length_1 = std::min(length, length_1);

		health_bar.setSize(sf::Vector2f(length,9.0f));
		health_bar.setOrigin(sf::Vector2f(0.0f, 0.0f));
		health_bar_1.setSize(sf::Vector2f(length_1, 9.0f));
		health_bar_1.setOrigin(sf::Vector2f(0.0f, 0.0f));
		if (player_ == 1)
		{
			health_bar.setPosition(sf::Vector2f(513.0f - length, 11.0f));
			health_bar_1.setPosition(sf::Vector2f(513.0f - length_1, 11.0f));
		}
		else
		{
			health_bar.setPosition(sf::Vector2f(849.0f,11.0f));
			health_bar_1.setPosition(sf::Vector2f(849.0f, 11.0f));
		}
		
		
	}
}