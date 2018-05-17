#include "Gameover_State.hpp"

namespace frost
{
	Gameover_State::Gameover_State(GameDataRef data, std::string text) : data_(data)
	{
		data->assets.LoadFont("arial", "Resources/fonts/arial.ttf");
		text_.setFont(data->assets.GetFont("arial"));
		
		text_.setCharacterSize(60);
		text_.setString(text);
		text_.setPosition(sf::Vector2f(500.0f, 300.0f));
	}
	void Gameover_State::Init()
	{

	}
	void Gameover_State::HandleInput()
	{

	}
	void Gameover_State::Update(float dt)
	{
		
		clock += dt;
		if(clock>=5.0f)
			this->data_->machine.AddState(StateRef(new Choosing_State(data_)), true);
	}

	void Gameover_State::Draw(float dt)
	{
		
		this->data_->window.clear(sf::Color::Black);
		
		data_->window.draw(text_);
		
		data_->window.display();
	}
}