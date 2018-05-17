#include "Choosing.hpp"

namespace frost
{
	Choosing_State::Choosing_State(GameDataRef data) :data_(data)
	{
		
		data->assets.LoadTexture("Choosing", "Resources/res/choose_player.png");
		data->assets.LoadTexture("Back_Ground", "Resources/res/back_ground_1.png");
		data->assets.LoadTexture("Choose", "Resources/res/choose.png");
		player1_2.setTexture(data_->assets.GetTexture("Choose"));
		player1_2.setPosition(sf::Vector2f(55.0f,0.0f));
		player2_2.setTexture(data_->assets.GetTexture("Choose"));
		player2_2.setPosition(sf::Vector2f(960.0f, 0.0f));
		back_ground.setTexture(data_->assets.GetTexture("Back_Ground"));
		choose.setTexture(data->assets.GetTexture("Choosing"));
		choose.setTextureRect(sf::IntRect(0, 0, 180 * 7, 180));
		choose.setPosition(sf::Vector2f(55.0f, 550.0f));
		player2.setTexture(data->assets.GetTexture("Choosing"));
		player2.setTextureRect(sf::IntRect(180 * 7, 0, 180, 180));
		player2_1.setTexture(data->assets.GetTexture("Choosing"));
		player2_1.setOrigin(sf::Vector2f(frame_size / 2.0f, frame_size));
		player2_1.setPosition(sf::Vector2f(860.0f, 500.0f));
		
		player1.setTexture(data->assets.GetTexture("Choosing"));
		player1.setTextureRect(sf::IntRect(180 * 8, 0, 180, 180));
		player1_1.setTexture(data->assets.GetTexture("Choosing"));
		player1_1.setOrigin(sf::Vector2f(frame_size / 2.0f, frame_size));
		player1_1.setPosition(sf::Vector2f(500.0f, 500.0f));
		
	}

	void Choosing_State::Init()
	{

	}
	void Choosing_State::HandleInput()
	{
		if (!key_lock_2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
			{
				key_lock_2 = true;
				switch ( play_2)
				{
				case 0:
				{
					name_2 = "zero";
					return;
				}
				case 1:
				{
					name_2 = "zero_black";
					return;
				}
				default:
					break;
				}
			}
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Right_2 = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Left_2 = true;
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Right_2)
			{
				Right_2 = false;
				play_2 = (play_2 + 1) % 7;
				frame_2 = 0;
			}
			else
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Left_2)
				{
					Left_2 = false;
					play_2 = (play_2 + 6) % 7;
					frame_2 = 0;
				}
				
			}
				
		}

		if (!key_lock_1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				key_lock_1 = true;
				switch (play_1)
				{
				case 0:
				{
					name_1 = "zero";
					return;
				}
				case 1:
				{
					name_1 = "zero_black";
					return;
				}
				default:
					break;
				}
			}
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Right_1 = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Left_1 = true;
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Right_1)
			{
				Right_1 = false;
				play_1 = (play_1 + 1) % 7;
				frame_1 = 0;
			}
			else
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Left_1)
				{
					Left_1 = false;
					play_1 = (play_1 + 6) % 7;
					frame_1 = 0;
				}

			}

		}
	}

	void Choosing_State::Update(float dt)
	{

		player1_2.setTextureRect(sf::IntRect(180 * play_1 * 2, 0, 360, 540));
		player2_2.setTextureRect(sf::IntRect(180 * play_2 * 2+360, 0, -360, 540));
		float frame_time_2 = 1 / 20.0f;
		if (frame_2 >= 12) frame_time_2 = 1.0f / 10.0f;
		clock_2 += dt;
		while (clock_2 >= frame_time_2)
		{
			clock_2 -= frame_time_2;
			frame_2++;
		}
		
		player2.setPosition(sf::Vector2f(choose.getPosition().x+play_2*180.0f, choose.getPosition().y));
		if (play_2 <= 1)
		{
			if (frame_2<= 7)
				player2_1.setTextureRect(sf::IntRect(180 * frame_2+180, 180 * 7 + 180 * 2 * play_2, -180, 180));
			else
			{
				if (frame_2 > 16) frame_2 = 13;
				player2_1.setTextureRect(sf::IntRect(180 * (frame_2 - 8)+180, 180 * 8 + 180 * 2 * play_2, -180, 180));
			}
		}
		else
		{

			if (frame_2 <= 8)

				player2_1.setTextureRect(sf::IntRect(180 * frame_2+180, 180, -180, 180));
			else
			{
				if (frame_2 > 15) frame_2 = 12;
				player2_1.setTextureRect(sf::IntRect(180 * (frame_2 - 9)+180, 180 * 2 + 180 * (play_2 - 2), -180, 180));
			}
				
		}

		float frame_time_1 = 1 / 20.0f;
		if (frame_1 >= 12) frame_time_1 = 1.0f / 10.0f;
		clock_1 += dt;
		while (clock_1 >= frame_time_1)
		{
			clock_1 -= frame_time_1;
			frame_1++;
		}

		player1.setPosition(sf::Vector2f(choose.getPosition().x + play_1 * 180.0f, choose.getPosition().y));
		if (play_1 <= 1)
		{
			if (frame_1 <= 7)
				player1_1.setTextureRect(sf::IntRect(180 * frame_1, 180 * 7 + 180 * 2 * play_1, 180, 180));
			else
			{
				if (frame_1 > 16) frame_1 = 13;
				player1_1.setTextureRect(sf::IntRect(180 * (frame_1 - 8), 180 * 8 + 180 * 2 * play_1, 180, 180));
			}
		}
		else
		{

			if (frame_1 <= 8)

				player1_1.setTextureRect(sf::IntRect(180 * frame_1, 180, 180, 180));
			else
			{
				if (frame_1 > 15) frame_1 = 12;
				player1_1.setTextureRect(sf::IntRect(180 * (frame_1 - 9), 180 * 2 + 180 * (play_1 - 2), 180, 180));
			}

		}
		if (key_lock_1 && key_lock_2)
		{
			
			this->data_->machine.AddState(StateRef(new GameState(data_,name_1,name_2)), true);
			return;
		}
	}
	void Choosing_State::Draw(float dt)
	{
		//std::cout << play_1 << " ";
		data_->window.clear();
		data_->window.draw(back_ground);
		data_->window.draw(choose);
		
		data_->window.draw(player1);
		data_->window.draw(player1_1);
		data_->window.draw(player1_2);

		data_->window.draw(player2);
		data_->window.draw(player2_1);
		data_->window.draw(player2_2);
		data_->window.display();
	}
}