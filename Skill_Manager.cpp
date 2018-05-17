#include "Skill_Manager.hpp"

namespace frost
{

	Skill::Skill(Skill_data data, GameDataRef game_data): data_(data),game_data_(game_data)
	{
		data_.clock = 0.0f;
		data_.framenum = 0;
		data_.sprite.setTexture(game_data_->assets.GetTexture(data_.texture));
		data_.sprite.setOrigin(data_.orgin);
		data_.sprite.setPosition(data_.pos);
	}
	
	
	Skill_data Skill::Get_Skill_data()
	{
		return data_;
	}

	

	void Skill::Update(float dt)
	{
		data_.clock += dt;
		while (data_.clock >= data_.frame_time)
		{
			data_.clock -= data_.frame_time;
			data_.framenum++;
		}
		if (data_.framenum >= data_.rect_num && data_.one_animation_skill)
		{
			data_.avaiable = false;
			return;
		}
		if (data_.framenum >= data_.pre_framenum)
			data_.sprite.setTextureRect(data_.rect[data_.framenum % (data_.rect_num - data_.pre_framenum) + data_.pre_framenum]);
		else
			data_.sprite.setTextureRect(data_.rect[data_.framenum]);
		data_.sprite.move(dt*data_.vector);
		
	}

	void Skill::Draw()
	{
		game_data_->window.draw(data_.sprite);
	}

	Skill_Manager::Skill_Manager(GameDataRef data__): data(data__)
	{
	}

	void Skill_Manager::AddSkill(Skill skill)
	{
		skill_.push_back(skill);
		
		
	}

	void  Skill_Manager::Add_Explosion(sf::Vector2f pos)
	{
		Skill_data skill_;
		skill_.orgin = sf::Vector2f(90.0f, 90.0f);
		skill_.rect = new sf::IntRect[17];
		skill_.pos = pos;
		skill_.texture = "Effect";
		skill_.rect_num = 17;
		skill_.frame_time = 1.0f / 60.0f;
		skill_.one_animation_skill = true;
		skill_.destroyable = false;
		for (int i = 0; i<17; i++)
			skill_.rect[i] = sf::IntRect(180 * i, 180*4, 180, 180);
		Skill skill(skill_, data);
		this->AddSkill(skill);
		

		
	}

	void Skill_Manager::Add_Player(Player* player_)
	{
		player = player_;
	}

	void Skill_Manager::Skill_Hit(Player *player,sf::Sprite player_sprite)
	{
		for (int i = 0; i < skill_.size(); i++)
		{
			if (skill_.at(i).Get_Skill_data().damage <= 0.0f) continue;
			if (skill_.at(i).Get_Skill_data().player == player->Get_status()->player_num) continue;
			sf::FloatRect rect_1 = skill_.at(i).Get_Skill_data().sprite.getGlobalBounds();
			
			sf::FloatRect rect_2 = player_sprite.getGlobalBounds();
			if (!rect_2.intersects(rect_1)) continue;
			if (Collision::PixelPerfectTest(skill_.at(i).Get_Skill_data().sprite, player_sprite))
			{
				player->HIT(skill_.at(i).Get_Skill_data().damage);
			}

		}
	}
	void Skill_Manager::Update(float dt)
	{
		for (int i = 0; i < skill_.size(); i++)
		{
			
			skill_.at(i).Update(dt);
			if (!skill_.at(i).Get_Skill_data().avaiable)
			{
				skill_.erase(skill_.begin() + i);
				continue;
			}
			if ( (skill_.at(i).Get_Skill_data().sprite.getPosition().x < -500.0f) || (skill_.at(i).Get_Skill_data().sprite.getPosition().x > 3000.0f) || (skill_.at(i).Get_Skill_data().sprite.getPosition().y< -500.0f) || (skill_.at(i).Get_Skill_data().sprite.getPosition().y > 1000.0f))
				skill_.erase(skill_.begin() + i);
		}

		for (int i=0;i<skill_.size();i++)
		{ 
			if (skill_.at(i).Get_Skill_data().damage == 0.0f) continue;
			for (int j = i + 1; j < skill_.size(); j++)
			{
				
				if (skill_.at(j).Get_Skill_data().damage ==0.0f ) continue;
				if (skill_.at(i).Get_Skill_data().player == skill_.at(j).Get_Skill_data().player) continue;
				sf::FloatRect rect_1 = skill_.at(i).Get_Skill_data().sprite.getGlobalBounds(), rect_2 = skill_.at(j).Get_Skill_data().sprite.getGlobalBounds();
				if (!rect_1.intersects(rect_2)) continue;
				if (!Collision::PixelPerfectTest(skill_.at(i).Get_Skill_data().sprite, skill_.at(j).Get_Skill_data().sprite)) continue;
				
				if (skill_.at(i).Get_Skill_data().damage == skill_.at(j).Get_Skill_data().damage)
				{
					
					if (skill_.at(j).Get_Skill_data().destroyable)
					{
						Add_Explosion(skill_.at(j).Get_Skill_data().sprite.getPosition());
						skill_.erase(skill_.begin() + j);
					}
					    
					if (skill_.at(i).Get_Skill_data().destroyable)
					{
						
						Add_Explosion(skill_.at(i).Get_Skill_data().sprite.getPosition());
						skill_.erase(skill_.begin() + i);
					}
					    
					continue;
				}

				if (skill_.at(i).Get_Skill_data().damage > skill_.at(j).Get_Skill_data().damage)
				{
					
					if (!skill_.at(j).Get_Skill_data().destroyable) continue;
					Add_Explosion(skill_.at(j).Get_Skill_data().sprite.getPosition());
					skill_.erase(skill_.begin() + j);
					continue;
				}

				if (skill_.at(i).Get_Skill_data().damage < skill_.at(j).Get_Skill_data().damage)
				{
					
					if (!skill_.at(i).Get_Skill_data().destroyable) continue;
					Add_Explosion(skill_.at(i).Get_Skill_data().sprite.getPosition());
					skill_.erase(skill_.begin() + i);
					continue;
				}
				
			}
		}
		
		

	}

	void Skill_Manager::Draw()
	{
		for (int i = 0; i < skill_.size(); i++)
         if (!skill_.at(i).Get_Skill_data().invisible)
			data->window.draw(skill_.at(i).Get_Skill_data().sprite);
	}
}