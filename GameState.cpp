#pragma once

#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <iostream>

namespace frost
{ 

	GameState::GameState(GameDataRef data,std::string name_1 , std::string name_2 ) : _data(data)
	{
		character = new Character;
		(*character).Init(_data,name_1,name_2);
		_data->assets.LoadTexture("Back_ground", "Resources/res/back_ground.png");
		Back_Ground.setTexture(_data->assets.GetTexture("Back_ground"));
		background_music.openFromFile("Resources/audio/background_music.wav");
		background_music.play();
		background_music.setLoop(true);
		
	}
	
	void GameState::Init()
	{
		

	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}

		
		(*character).HandleInput();
		
	}

	void GameState::Update(float dt)
		
	{
		//fps
		fps++;
		clock += dt;
		if (clock > 1.0f)
		{
			_data->window.setTitle("megaman vs zero " + std::to_string(fps) +" FPS");
			clock -= 1.0f;
			fps = 0;
		}
		

		(*character).Update(dt);

		// have to stop music or error
		if ((*character).End())
			background_music.stop();


	}

	void GameState::Draw(float dt)
	{
		
		this->_data->window.clear();
		_data->window.draw(Back_Ground);
		character->Draw();
		this->_data->window.display();
		
	}

}