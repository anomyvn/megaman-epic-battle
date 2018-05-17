#pragma once

#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include <SFML\Audio.hpp>
#include <string>



namespace frost
{
	
	//class Character;
	class GameState : public State
	{
	public:
		GameState(GameDataRef data,std::string name_1 ="",std::string name_2 = "");

		void Init();
		
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Sprite Back_Ground;
		Character *character;
		sf::Music background_music;


		//fps 
		float clock=0.0f;
		int fps=0;

	    //Character character; sẽ xảy ra lỗi d vui vẻ lắm
	    //https://stackoverflow.com/questions/18766089/undefined-class-error-in-c?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
		
	};
}