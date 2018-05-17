#include "zero.hpp"

namespace frost
{
    Zero::Zero(GameDataRef data__, Key *key_, Skill_Manager *skill_manager, int player,std::string name): data(data__), key(key_), skill_manager_(skill_manager)
	{
	     
		 key_num = player;
		 direct = 1;
		 framenum_air_attack = 0;
		 framenum = 0;
		 clock = 0;
		 velocity_x = velocityx;
		 velocity_y = velocityy;
		 keylock = false;
		 air_attack = false;
		 time = 0.0f;
		 change_attribute_hold = false;
		
		 
		 status.Attack = 100.0f;
		 status.Def = 100.0f;
		 status.Health = 2000.0f;
		 status.Max_Health = 2000.0f;
		 status.Max_Mana = 2000.0f;
		 status.Mana = 1000.0f;
		 status.attribute = lightning;
		 status.type = zero;
		 status.player_num = player;
		 
		 
		 for (int i = 0; i < 16; i++) Giga_frame[i] = sf::IntRect((i%8)*frame_size*3,(i / 8 +2) * frame_size, frame_size * 3, frame_size);
		 for (int i = 16; i < 24; i++) Giga_frame[i] = sf::IntRect(i % 8 * frame_size*3, frame_size * 4, frame_size * 3, frame_size * 3);
		 for (int i = 24; i < 30; i++) Giga_frame[i] = sf::IntRect((29 - i)*frame_size * 2, frame_size * 35, frame_size * 2, frame_size);
		 for (int i = 30; i < 36; i++) Giga_frame[i] = sf::IntRect((i - 30)*frame_size * 2, frame_size * 35, frame_size * 2, frame_size);
		 for (int i = 36; i < 58; i++) Giga_frame[i] = sf::IntRect((i - 36)*frame_size, frame_size * 37, frame_size, frame_size * 3);
		 for (int i = 58; i < 68; i++) Giga_frame[i] = sf::IntRect((i - 58)*frame_size * 2 + frame_size * 22, frame_size * 38, frame_size * 2, frame_size * 2);
		 
		 
		
		 //this shitty code cost more 200MB Ram than it 's supposed to be
		 //dont know why
		 /*
		 data->assets.LoadTexture("Effect", "Resources/res/effect.png");
		 data->assets.LoadTexture("Zero_skill", "Resources/res/Zero_skill.png");
		 data->assets.LoadTexture("Saber", "Resources/res/saber.png");
		 data->assets.LoadTexture("Zero", "Resources/res/Zero.png");
		 */
		 if (name =="zero")
		 sprite.setTexture(data->assets.GetTexture("Zero"));
		 else
			 sprite.setTexture(data->assets.GetTexture("Zero_Black"));
		 
		 data->assets.LoadTexture("Zero_clone", "Resources/res/Zero_1.png");
		 sprite_.setTexture(data->assets.GetTexture("Zero_clone"));
		 sprite_.setTextureRect(sf::IntRect(frame_size * 3, 0, frame_size, frame_size));
		 sprite_.setOrigin(sf::Vector2f(frame_size / 2.0f, frame_size));
		 
		 
		 Giga_sprite.setTexture(data->assets.GetTexture("Effect"));
		 
		 Maverick_Zero_1.setTexture(data->assets.GetTexture("Effect"));
		 Maverick_Zero_2.setTexture(data->assets.GetTexture("Effect"));
		 Maverick_Zero_1.setOrigin(sf::Vector2f(frame_size , frame_size*2.0f - 30.0f));
		 Maverick_Zero_2.setOrigin(sf::Vector2f(frame_size, frame_size));
		 
		 
		
		 sprite.setOrigin(frame_size/2.0f, frame_size);
		 sprite.setPosition(500.0f, Ground);
	
		 player_state = new Standing_State((Player*)(this));
		 
		 
	}
	Status *Zero::Get_status()
	{
		return (&status);
	}

	sf::Sprite  Zero::Get_Sprite()
	{
		return (sprite_);
	}

	void Zero::HIT(float damage)
	{
		if (invisible) return;
		status.Health -= damage;
		status.Health = std::max(0.0f, status.Health);
		invisible = true;
		keylock = true;
		hit = true;
		framenum = 0;
	}

	void Zero::Hit_State()
	{
		invisible = true;
		sprite.setOrigin(sf::Vector2f(frame_size / 2.0f, frame_size));
		while (clock >= 1.0 / 20.0f)
		{
			clock -= 1.0f / 20.0f;
			framenum++;
		}
		if (framenum > 6)
		{
			hit = false;
			keylock = false;
			hit_time = 1.0f;
			if (sprite.getPosition().y < Ground) player_state = new Falling_State((Player*)this);
			else player_state = new Standing_State((Player*)this);
			return;
		}
		sprite.setTextureRect(sf::IntRect(frame_size*framenum, frame_size * 17, frame_size, frame_size));

	}
	Key_lock Zero::Get_Key_lock()
	{
		return key_lock;
	}
 	void Zero::HandleInput()
	{
		if (keylock) return;
		
		if (hit_time > 0.0f) invisible = true;
		else invisible = false;

		if (sprite.getPosition().x <= 150.0f)
		{
				
			sprite.setPosition(150.0f, sprite.getPosition().y);
			key_lock.left_lock = 1.0f;
		}
		else key_lock.left_lock = 0.0f;
		
		
		if (sprite.getPosition().x >= 1366.0f-150.0f)
		{
			sprite.setPosition(1366.0f-150.0f, sprite.getPosition().y);
			key_lock.right_lock = 1.0f;
		}
		else key_lock.right_lock = 0.0f;
		
		//wall sliding
		if (on_air && key_lock.left_lock == 1.0f && !sliding &&key[key_num]["left"])
		{
			player_state = new Wall_Sliding_State((Player*)this);
			return;
		}
		if (on_air && key_lock.right_lock == 1.0f && !sliding &&key[key_num]["right"])
		{
			player_state = new Wall_Sliding_State((Player*)this);
			return;
		}

		//change attribute
		if (change_attribute_hold && !sf::Keyboard::isKeyPressed(key[key_num]["change_attribute"]))
		{
			change_attribute_hold = false;
			status.attribute = static_cast<Attribute>((status.attribute+1)%4);
		}
		   
		if (sf::Keyboard::isKeyPressed(key[key_num]["change_attribute"]))
			change_attribute_hold = true;


		if (sf::Keyboard::isKeyPressed(key[key_num]["left"]))
		{
			direct = 0;
		}
		if (sf::Keyboard::isKeyPressed(key[key_num]["right"]))
		{
			direct = 1;
		}
		player_state=player_state->HandleInput(key,key_num);
	}
	void Zero::Update_key_lock()
	{
		if (key_lock.attack_lock >= 0.0f) key_lock.attack_lock -= dt_;
		if (key_lock.dash_lock >= 0.0f) key_lock.dash_lock -= dt_;
		if (hit_time >= 0.0f) hit_time -= dt_;
	}
	void Zero::Update(float dt)
	{
		clock += dt;
		dt_ = dt;
		Update_key_lock();
		if (maverick_zero_mode)
		{
			clock_maverick += dt;
			while (clock_maverick >= 1.0f / 30.0f)
			{
				maverick_framenum++;
				clock_maverick -= 1.0f / 30.0f;
			}
			Maverick_Zero_1.setTextureRect(sf::IntRect((maverick_framenum %4)*frame_size*2,frame_size*2,frame_size*2,frame_size*2));
			Maverick_Zero_2.setTextureRect(sf::IntRect((maverick_framenum % 4 * 2 + 4)*frame_size, frame_size * 2, frame_size * 2, frame_size));
			Maverick_Zero_1.setPosition(sprite.getPosition());
			Maverick_Zero_2.setPosition(sprite.getPosition());
			

		}
		if (hit)
		{
			Hit_State();
			return;
		}
		if (hit_time > 0.0f) sprite.setColor(sf::Color(255, 255, 255, 200));
		else sprite.setColor(sf::Color(255, 255, 255, 255));
		player_state->Update();
		sprite_.setPosition(sprite.getPosition());
	}
	void Zero::Draw()
	{
		//sprite.setScale(sf::Vector2f(2.0f, 2.0f));
		
		if (giga_effect)
			data->window.draw(Giga_sprite);
		if (maverick_zero_mode) {
			data->window.draw(Maverick_Zero_1);
			data->window.draw(Maverick_Zero_2);
		}
		data->window.draw(sprite);

	}

	void Zero::Reset()
	{
		last_frame_attack = -1;
		sprite.setOrigin(frame_size / 2.0f, frame_size);
		sliding = false;
		circle = 0;
		giga_effect = false;
		last_direct = direct;
		framenum = 0;
		using_skill = false;
		velocity_y = velocityy;
		time = 0.0f;
	}
	void Zero::Attack()
	{
		
		keylock = true;
		sprite.setOrigin(frame_size*3.0f / 2.0f, frame_size );
		int num_of_frame = 8;
		float frame = 1.0f/40.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}

		if (framenum == 3 && !using_skill)
		{
			
			Skill_data skill_;
			using_skill = true;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 100, 50);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x+50.0f, sprite.getPosition().y-100.0f);
				
			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 160.0f, sprite.getPosition().y-100.0f);
				
			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame * 3.0f;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum == 4)
		{
			using_skill = false;
		}

		//ending attack
		if (framenum >= 1000)
		{
			Rut_Kiem();
			return;
		}

		//attack combo
		if (framenum >= 400)
		{
			Attack_2();
			return;
		}
		if (framenum >= 200)
		{
			Attack_1();
			return;
		}


		if (framenum >= num_of_frame)
		{
			// combo attack move to 1
			if (sf::Keyboard::isKeyPressed(key[key_num]["attack"]))
			{
				framenum = 200; //in case lag
				return;
			}
			framenum = 1000;
			return;
		}

		

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size*3 * framenum , frame_size*2, frame_size*3, frame_size));
		else
			sprite.setTextureRect(sf::IntRect(frame_size*3 *(framenum+1), frame_size*2, -frame_size*3, frame_size));
			
	}

	void Zero::Attack_1()
	{
		int num_of_frame = 8;
		if (framenum >= 200+8)
		{
			// combo attack move to 2
			if (sf::Keyboard::isKeyPressed(key[key_num]["attack"]))
			{
				framenum = 400;
				return;
			}
			framenum = 1000;
			return;
		}

		if (framenum == 203 && !using_skill)
		{

			Skill_data skill_;
			using_skill = true;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 100, 100);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 50.0f, sprite.getPosition().y - 100.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 160.0f, sprite.getPosition().y - 100.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = 1/30.0f * 3.0f;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum >= 204)
		{
			using_skill = false;
		}

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum-200), frame_size * 3, frame_size * 3, frame_size));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum + 1-200), frame_size * 3, -frame_size * 3, frame_size));

	}

	void Zero::Attack_2()
	{
		sprite.setOrigin(frame_size*3.0f / 2.0f, frame_size*2.0f);
		int num_of_frame = 8;
		if (framenum >= num_of_frame + 400)
		{
			framenum = 1000;
			return;
			
		}
		if (framenum >= 400+4 && !using_skill)
		{


			Skill_data skill_;

			skill_.orgin = sf::Vector2f(0.0f, 180.0f);
			skill_.rect = new sf::IntRect[4];
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
				skill_.vector = sf::Vector2f(600.0f, 0.0f);
				for (int i = 0; i < 4; i++) skill_.rect[i] = sf::IntRect(180 * i + 4 * 180 * status.attribute, 180, 180, 180);
			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x -180.0f , sprite.getPosition().y );
				skill_.vector = sf::Vector2f(-600.0f, 0.0f);
				for (int i = 0; i < 4; i++) skill_.rect[i] = sf::IntRect(180 * i + 1 + 4 * 180 * status.attribute, 180*20, 180, 180);
			}

			
			skill_.player = status.player_num;
			skill_.damage = 50.0f;
			skill_.texture = "Zero_skill";
			skill_.rect_num = 4;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
			using_skill = true;
		}

		
		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum - 400), frame_size * 4, frame_size * 3, frame_size*3));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum + 1 - 400), frame_size * 4, -frame_size * 3, frame_size*3));
	}

	void Zero::Rut_Kiem()
	{
		sprite.setOrigin(frame_size / 2.0f, frame_size);
		int num_of_frame = 6;
		if (framenum >= 1000 + num_of_frame)
		{
			keylock = false;
			player_state = new Standing_State((Player*)this);
			return;
		}

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size  * (framenum-1000), frame_size * 7, frame_size , frame_size));
		else
			sprite.setTextureRect(sf::IntRect(frame_size  * (framenum + 1-1000), frame_size *7, -frame_size , frame_size));
	}

	void Zero::Dash()
	{
		//speed up when dash
		// dash + jump can also speed up
		// slow down when stand
		

		float frame =  1.0f/30.0f;

		// dumb way to do
		if (framenum == 0) set_off = sprite.getPosition().x;


		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		if (!sf::Keyboard::isKeyPressed(key[key_num]["dash"]) || (abs(sprite.getPosition().x-set_off)>=300.0f) || (key_lock.left_lock==1.0f && direct ==0) || (key_lock.right_lock == 1.0f && direct == 1))
		{
			velocity_x = velocityx * 1.5f;
			//after dashing effect
			framenum = std::max(6, framenum);
		}
		else
		{
          //dashing effect
		  velocity_x = velocityx * 2.5f;
          if (framenum >= 3)
			framenum = (framenum % 3) + 3;
		}
		 
		if (framenum > 9)
		{
			key_lock.dash_lock = 0.1f;
			player_state = new Standing_State((Player*)this);
			return;
		}

		if (last_direct != direct) player_state = new Running_State((Player*)this);
		if (direct == 1)
		{
			sprite.setTextureRect(sf::IntRect(frame_size * framenum, frame_size*11, frame_size, frame_size));
			sprite.move(velocity_x*dt_);
		}

		else
		{
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum+1), frame_size*11, -frame_size, frame_size));
			sprite.move(-velocity_x * dt_);
		}
		last_direct = direct;
	}
	void Zero::Duck()
	{
		
		float frame = 1.0f/60.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		framenum = std::min(1, framenum);
		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * framenum , frame_size * 20, frame_size, frame_size));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum+1), frame_size * 20, -frame_size, frame_size));
			
	}
	void Zero::On_air_attack()
	{
		sprite.setOrigin(frame_size * 3.0f / 2.0f, frame_size * 2.0f);
		int num_of_frame = 8;
		float frame = 1.0f / 60.0f;
		while (clock1 >= frame)
		{
			clock1 -= frame;
			framenum_air_attack++;
		}


		if (framenum_air_attack == 0 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = 0;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 120, 80);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 20.0f, sprite.getPosition().y - 180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 160.0f, sprite.getPosition().y - 180.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame ;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 1 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = 1;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 100, 180);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 70.0f, sprite.getPosition().y-180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 170.0f, sprite.getPosition().y-180.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 2 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = 2;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 120, 160);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 20.0f, sprite.getPosition().y-40.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 140.0f, sprite.getPosition().y-40.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 3 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = framenum_air_attack;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 240, 130);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 90.0f, sprite.getPosition().y);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 170.0f, sprite.getPosition().y);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 4 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = 4;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 150, 100);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 150.0f, sprite.getPosition().y-30.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y-30.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 5 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = framenum_air_attack;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 120, 180);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 120.0f, sprite.getPosition().y-100.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x , sprite.getPosition().y-100.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 6 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = framenum_air_attack;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 150, 100);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 150.0f, sprite.getPosition().y-180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x , sprite.getPosition().y-180.0f);

			}
			
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum_air_attack == 7 && framenum_air_attack != last_frame_attack)
		{
			last_frame_attack = framenum_air_attack;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 180, 110);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 90.0f, sprite.getPosition().y-180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 90.0f, sprite.getPosition().y-180.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}
		if (framenum_air_attack >= num_of_frame)
		{
			air_attack = false;
			return;
		}	
		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * framenum_air_attack, frame_size * 21, frame_size * 3, frame_size * 3));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum_air_attack + 1), frame_size * 21, -frame_size * 3, frame_size * 3));
	}
	
	void Zero::On_air_Special_attack()
	{
		sprite.setOrigin(frame_size / 2.0f, frame_size * 2.0f);
		float frame = 1 / 30.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}

		if (sprite.getPosition().y >= Ground)
		{
			// tiep dat
			if (!using_skill)
			{
				Skill_data skill_;
				skill_.orgin = sf::Vector2f(90.0f, 180.0f-20.0f);
				skill_.rect = new sf::IntRect[17];
				skill_.pos = sprite.getPosition();
				skill_.texture = "Effect";
				skill_.rect_num = 17;
				skill_.frame_time = 1.0f / 60.0f;
				skill_.one_animation_skill = true;
				for (int i = 0; i<17; i++)
					skill_.rect[i] = sf::IntRect(frame_size   * i, frame_size * 4, frame_size , frame_size);
				Skill skill(skill_, data);
				skill_manager_->AddSkill(skill);
				using_skill = true;

				skill_.orgin = sf::Vector2f(120.0f, 180.0f);
				Skill skill1(skill_, data);
				skill_manager_->AddSkill(skill1);
			}
			sprite.setPosition(sprite.getPosition().x, Ground);
			framenum = std::max(5, framenum);
			if (framenum >= 10)
			{
				sprite.setOrigin(frame_size / 2.0f, frame_size);
				player_state = new Standing_State((Player*)this);
				return;
			}
			if (direct == 1)
				sprite.setTextureRect(sf::IntRect(15 * frame_size + frame_size * framenum, frame_size * 14, frame_size, frame_size * 3));
			else
				sprite.setTextureRect(sf::IntRect(15 * frame_size + frame_size * (framenum + 1), frame_size * 14, -frame_size, frame_size * 3));
		}
		else
		{
			if (framenum >= 1) framenum = 1 + (framenum % 4);
			Skill_data skill_;
			
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 40, 190);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 15.0f, sprite.getPosition().y - 80.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 60.0f, sprite.getPosition().y - 100.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = 1 / 30.0f * 3.0f;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
			sprite.move(-dt_ * velocity_y);
			if (sf::Keyboard::isKeyPressed(key[key_num]["left"])) sprite.move(-velocity_x * dt_);
			if (sf::Keyboard::isKeyPressed(key[key_num]["right"])) sprite.move(velocity_x * dt_);
			if (direct == 1)
				sprite.setTextureRect(sf::IntRect(frame_size * framenum + frame_size * status.attribute * 5, frame_size * 14, frame_size, frame_size * 3));
			else
				sprite.setTextureRect(sf::IntRect(frame_size * (framenum + 1) + frame_size * status.attribute * 5, frame_size * 14, -frame_size, frame_size * 3));
		}

		

	}

	void Zero::Jump()
	{
		on_air = true;
		sprite.setOrigin(frame_size / 2.0f, frame_size);
		float frame = 1/45.0f;
		
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;	
		}
		
		if (Ground - sprite.getPosition().y >= Max_height)
		{
			player_state = new Falling_State((Player*)this);
			return;
		}

		//caculate sprite position
		if (sf::Keyboard::isKeyPressed(key[key_num]["left"])) sprite.move(-velocity_x*dt_);
		if (sf::Keyboard::isKeyPressed(key[key_num]["right"])) sprite.move(velocity_x * dt_);
		time += dt_;
		velocity_y.y = velocityy.y + Gravity*time;
		sprite.move(velocity_y*dt_);
		
		// jumping frame
		if (framenum > 1) framenum = (framenum % 3) + 2;
		

	
		

		if (air_attack) clock1 += dt_;
		if ((sf::Keyboard::isKeyPressed(key[key_num]["attack"])) && (key_lock.attack_lock<=0.0f) && (!air_attack)) {

			framenum_air_attack = 0;
			air_attack = true;
			key_lock.attack_lock= 0.5;
			clock1 = 0.0f;
		}
		if (air_attack)
		{
			On_air_attack();
			return;
		}
		if (direct == 1) sprite.setTextureRect(sf::IntRect(frame_size * framenum, frame_size * 8, frame_size, frame_size));
		else sprite.setTextureRect(sf::IntRect(frame_size * (framenum + 1), frame_size * 8, -frame_size, frame_size));
	}
	void Zero::Run()
	{
		int num_of_frame=14;
		float frame =1.0f/30.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		
		if (direct == 1)
		{ 
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum % num_of_frame), frame_size, frame_size, frame_size));
			sprite.move(velocity_x*dt_);
		}
			
		else
		{ 
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum % num_of_frame + 1), frame_size, -frame_size, frame_size));
			sprite.move(-velocity_x * dt_);
		}
			
	}
	void Zero::Stand()
	{
		sprite.setOrigin(frame_size / 2.0f, frame_size);
		key_lock.jump_lock = 0.0f;
		float frame=1/10.0f ;
		velocity_x = velocityx;
		air_attack = false;
		on_air = false;

		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		
		if (direct == 1)

			sprite.setTextureRect(sf::IntRect(frame_size * (framenum % 6), 0, frame_size, frame_size));
		else
		
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum % 6 + 1), 0, -frame_size, frame_size));
			
		
		
	}
	void Zero::Fall()
	{
		sprite.setOrigin(frame_size / 2.0f, frame_size * 2.0f);
		float frame = 1/30.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		
		if (sprite.getPosition().y >= Ground)
		{
			// tiep dat
			sprite.setPosition(sprite.getPosition().x,Ground);
			framenum = std::max(7, framenum);
			if (framenum >= 8)
			{
				sprite.setOrigin(frame_size / 2, frame_size);
				if (direct == 1)
					sprite.setTextureRect(sf::IntRect(frame_size * framenum, frame_size * 11, frame_size, frame_size*2));
				else
					sprite.setTextureRect(sf::IntRect(frame_size* (framenum + 1), frame_size * 11, -frame_size, frame_size*2));
				player_state = new Standing_State((Player*)this);
				
				return;
			}
		}
		else
		{
			if (framenum >= 3) framenum = 3 + (framenum % 4);
			time += dt_;
			velocity_y.y = velocityy.y/1.5f- Gravity*time;
			sprite.move(-dt_*velocity_y);
			if (sf::Keyboard::isKeyPressed(key[key_num]["left"])) sprite.move(-velocity_x * dt_);
			if (sf::Keyboard::isKeyPressed(key[key_num]["right"])) sprite.move(velocity_x * dt_);
		}
		
		

		if (air_attack) clock1 += dt_;
		if ((sf::Keyboard::isKeyPressed(key[key_num]["attack"])) && (key_lock.attack_lock<=0.0f) && (!air_attack)) {

			framenum_air_attack = 0;
			air_attack = true;
			key_lock.attack_lock = 0.5f;
			clock1 = 0.0f;
		}
		if (air_attack)
		{
			On_air_attack();
			return;
		}

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * framenum, frame_size * 9, frame_size, frame_size * 2));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum + 1), frame_size * 9, -frame_size, frame_size * 2));
	}

	void Zero::Special_Attack()
	{
		keylock = true;
		int num_of_frame = 8;
		float frame = 1.0f/15.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}

		// ti fix
		if (framenum >= 2 && !using_skill)
		{

			Skill_data skill_;
			
			skill_.orgin = sf::Vector2f(0.0f, 90.0f);
			skill_.rect = new sf::IntRect[4];
			for (int i = 0; i < 4; i++) skill_.rect[i] = sf::IntRect(180 * i + 4 * 180 * status.attribute, 0, 180, 180);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 140.0f);
				skill_.vector = sf::Vector2f(600.0f, 0.0f);
				
			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x-180.0f, sprite.getPosition().y - 140.0f);
				skill_.vector = sf::Vector2f(-600.0f, 0.0f);
				if (status.attribute==neutral)
				  for (int i = 0; i < 4; i++) skill_.rect[i] = sf::IntRect(180 * (i+16), 0, 180, 180);
			}
			skill_.damage = 50.0f;
			skill_.player = status.player_num;
			skill_.texture = "Zero_skill";
			skill_.rect_num = 4;
			Skill skill(skill_,data);
			skill_manager_->AddSkill(skill);
			using_skill = true;
		}

		if (framenum >= num_of_frame)
		{
			keylock = false;
			player_state = new Standing_State((Player*)this);
			return;
		}

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * framenum , frame_size * 19, frame_size, frame_size));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum +1), frame_size * 19, -frame_size, frame_size));

	}
	
	void Zero::Duck_Attack()
	{
		sprite.setOrigin(frame_size * 3.0f /2.0f, frame_size * 2.0f);
		keylock = true;
		int num_of_frame = 8;
		float frame = 1.0f / 60.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		if (framenum == 0 && framenum != last_frame_attack)
		{
			last_frame_attack = 0;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 120, 80);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 20.0f, sprite.getPosition().y - 180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 160.0f, sprite.getPosition().y - 180.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum== 1 && framenum!= last_frame_attack)
		{
			last_frame_attack = 1;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 100, 180);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 70.0f, sprite.getPosition().y - 180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 170.0f, sprite.getPosition().y - 180.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum == 2 && framenum != last_frame_attack)
		{
			last_frame_attack = 2;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 120, 160);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x + 20.0f, sprite.getPosition().y - 40.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 140.0f, sprite.getPosition().y - 40.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum== 3 && framenum != last_frame_attack)
		{
			last_frame_attack = framenum;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 240, 130);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 90.0f, sprite.getPosition().y);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 170.0f, sprite.getPosition().y);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum == 4 && framenum != last_frame_attack)
		{
			last_frame_attack = 4;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 150, 100);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 150.0f, sprite.getPosition().y - 30.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 30.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum == 5 && framenum != last_frame_attack)
		{
			last_frame_attack = framenum;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 120, 180);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 120.0f, sprite.getPosition().y - 100.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 100.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum== 6 && framenum != last_frame_attack)
		{
			last_frame_attack = framenum;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 150, 100);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 150.0f, sprite.getPosition().y - 180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 180.0f);

			}

			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}

		if (framenum == 7 && framenum != last_frame_attack)
		{
			last_frame_attack = framenum;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 180, 110);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 90.0f, sprite.getPosition().y - 180.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 90.0f, sprite.getPosition().y - 180.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}
		if (framenum >= num_of_frame)
		{
			keylock = false;
			player_state = new Ducking_State((Player*)this);
			sprite.setOrigin(frame_size / 2.0f, frame_size);
			return;
		}

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size*3 * framenum, frame_size * 21, frame_size*3, frame_size*3));
		else
			sprite.setTextureRect(sf::IntRect(frame_size*3 * (framenum + 1), frame_size * 21, -frame_size*3, frame_size*3));

	}

	void Zero::Duck_Special_Attack()
	{
		sprite.setOrigin(frame_size * 3.0f / 2.0f, frame_size * 2.0f);
		keylock = true;
		int num_of_frame = 14;
		float frame = 1.0f / 25.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}

		//after special effect
		if (framenum >= num_of_frame)
		{
			if (framenum >= num_of_frame + 8)
			{
				keylock = false;
				player_state = new Ducking_State((Player*)this);
				sprite.setOrigin(frame_size / 2.0f, frame_size );
				return;
			}
			if (direct == 1)
				sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum), frame_size * 24, frame_size * 3, frame_size * 3));
			else
				sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum+1), frame_size * 24, frame_size * 3, frame_size * 3));
		}
		
		if (status.attribute == 1 && !using_skill && framenum == 8)
		{
			Skill_data skill_;
			skill_.player = status.player_num;
			skill_.damage = 30.0f;
			skill_.orgin = sf::Vector2f(90.0f, 90.0f);
			skill_.rect = new sf::IntRect[4];
			skill_.pos = sf::Vector2f(700.0f, 700.0f);
			skill_.vector = sf::Vector2f(0.0f, -1000.0f);
			for (int i = 0; i<4; i++)
				skill_.rect[i] = sf::IntRect(frame_size*i, frame_size * 8, frame_size, frame_size);
			skill_.texture = "Zero_skill";
			skill_.rect_num = 4;

			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);


			skill_.pos = sf::Vector2f(900.0f, 700.0f);
			Skill skill1(skill_, data);
			skill_manager_->AddSkill(skill1);
			
			skill_.pos = sf::Vector2f(1100.0f, 700.0f);
			Skill skill2(skill_, data);
			skill_manager_->AddSkill(skill2);

			skill_.pos = sf::Vector2f(500.0f, 700.0f);
			Skill skill3(skill_, data);
			skill_manager_->AddSkill(skill3);

			skill_.pos = sf::Vector2f(300.0f, 700.0f);
			Skill skill4(skill_, data);
			skill_manager_->AddSkill(skill4);

			using_skill = true;
			
		}

		if (status.attribute == 2 && !using_skill && framenum == 8)
		{
			Skill_data skill_;
			skill_.destroyable = false;
			skill_.damage = 60.0f;
			skill_.player = status.player_num;
			skill_.orgin = sf::Vector2f(0.0f, 180.0f);
			skill_.rect = new sf::IntRect[20];
			skill_.pos = sf::Vector2f(0.0f, Ground);
			for (int i = 0; i<20; i++)
				skill_.rect[i] = sf::IntRect(0, frame_size * (9+i%6), frame_size*11, frame_size);
			skill_.texture = "Zero_skill";
			skill_.rect_num = 20;
			skill_.one_animation_skill = true;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
			using_skill = true;

		}
		// neutral 
		if (framenum >= 8 && !using_skill && status.attribute ==0)
		{
			Skill_data skill_;
			skill_.player = status.player_num;
			skill_.damage = 30.0f;
			skill_.orgin = sf::Vector2f(90.0f, 180.0f);
			skill_.rect = new sf::IntRect[4];
			skill_.pos = sprite.getPosition();
			skill_.vector = sf::Vector2f(0.0f, -1000.0f);
			for (int i=0;i<4;i++)
				 skill_.rect[i] = sf::IntRect(frame_size*i, frame_size * 2, frame_size, frame_size);
			skill_.texture = "Zero_skill";
			skill_.rect_num = 4;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
			using_skill = true;


			Skill_data skill_1;
			skill_1.player = status.player_num;
			skill_1.damage = 30.0f;
			skill_1.orgin = sf::Vector2f(90.0f, 180.0f);
			skill_1.rect = new sf::IntRect[4];
			skill_1.pos = sprite.getPosition();
			skill_1.texture = "Zero_skill";
			skill_1.rect_num = 4;
			skill_1.vector = sf::Vector2f(-450.0f, -900.0f);
			for (int i = 0; i<4; i++)
				skill_1.rect[i] = sf::IntRect(frame_size*i, frame_size * 3, frame_size, frame_size);
			Skill skill1(skill_1, data);
			skill_manager_->AddSkill(skill1);

			Skill_data skill_2;
			skill_2.player = status.player_num;
			skill_2.damage = 30.0f;
			skill_2.orgin = sf::Vector2f(90.0f, 180.0f);
			skill_2.rect = new sf::IntRect[4];
			skill_2.pos = sprite.getPosition();
			skill_2.texture = "Zero_skill";
			skill_2.rect_num = 4;
			skill_2.vector = sf::Vector2f(450.0f, -900.0f);
			for (int i = 0; i<4; i++)
				skill_2.rect[i] = sf::IntRect(frame_size*(i+4), frame_size * 3, frame_size, frame_size);
			Skill skill2(skill_2, data);
			skill_manager_->AddSkill(skill2);
			

			Skill_data skill_3;
			skill_3.player = status.player_num;
			skill_3.damage = 30.0f;
			skill_3.orgin = sf::Vector2f(180.0f, 180.0f);
			skill_3.rect = new sf::IntRect[4];
			skill_3.pos = sprite.getPosition();
			skill_3.texture = "Zero_skill";
			skill_3.rect_num = 4;
			skill_3.vector = sf::Vector2f(-700.0f, -700.0f);
			for (int i = 0; i<4; i++)
				skill_3.rect[i] = sf::IntRect(frame_size*2*i, frame_size * 4, frame_size*2, frame_size);
			Skill skill3(skill_3, data);
			skill_manager_->AddSkill(skill3);

			
			skill_3.rect = new sf::IntRect[4];
			skill_3.vector = sf::Vector2f(700.0f, -700.0f);
			for (int i = 0; i<4; i++)
				skill_3.rect[i] = sf::IntRect(frame_size * 2 * (i+4), frame_size * 4, frame_size * 2, frame_size);
			Skill skill4(skill_3, data);
			skill_manager_->AddSkill(skill4);

			
			Skill_data skill_5;
			skill_5.player = status.player_num;
			skill_5.damage = 30.0f;
			skill_5.orgin = sf::Vector2f(180.0f, 180.0f-20.0f);
			skill_5.rect = new sf::IntRect[4];
			skill_5.pos = sprite.getPosition();
			skill_5.texture = "Zero_skill";
			skill_5.rect_num = 4;
			skill_5.vector = sf::Vector2f(-900.0f, -450.0f);
			for (int i = 0; i<4; i++)
				skill_5.rect[i] = sf::IntRect(frame_size * 2 * i, frame_size * 5, frame_size * 2, frame_size);
			Skill skill5(skill_5, data);
			skill_manager_->AddSkill(skill5);

			Skill_data skill_6;
			skill_6.player = status.player_num;
			skill_6.damage = 30.0f;
			skill_6.orgin = sf::Vector2f(180.0f, 180.0f - 20.0f);
			skill_6.rect = new sf::IntRect[4];
			skill_6.pos = sprite.getPosition();
			skill_6.texture = "Zero_skill";
			skill_6.rect_num = 4;
			skill_6.vector = sf::Vector2f(900.0f, -450.0f);
			for (int i = 0; i<4; i++)
				skill_6.rect[i] = sf::IntRect(frame_size * 2 * (i+4), frame_size * 5, frame_size * 2, frame_size);
			Skill skill6(skill_6, data);
			skill_manager_->AddSkill(skill6);
			

			Skill_data skill_7;
			skill_7.player = status.player_num;
			skill_7.damage = 30.0f;
			skill_7.orgin = sf::Vector2f(180.0f, 180.0f );
			skill_7.rect = new sf::IntRect[4];
			skill_7.pos = sprite.getPosition();
			skill_7.texture = "Zero_skill";
			skill_7.rect_num = 4;
			skill_7.vector = sf::Vector2f(-1000.0f, 0.0f);
			for (int i = 0; i<4; i++)
				skill_7.rect[i] = sf::IntRect(frame_size * 2 * i, frame_size * 6, frame_size * 2, frame_size);
			Skill skill7(skill_7, data);
			skill_manager_->AddSkill(skill7);

			Skill_data skill_8;
			skill_8.player = status.player_num;
			skill_8.damage = 30.0f;
			skill_8.orgin = sf::Vector2f(180.0f, 180.0f);
			skill_8.rect = new sf::IntRect[4];
			skill_8.pos = sprite.getPosition();
			skill_8.texture = "Zero_skill";
			skill_8.rect_num = 4;
			skill_8.vector = sf::Vector2f(1000.0f, 0.0f);
			for (int i = 0; i<4; i++)
				skill_8.rect[i] = sf::IntRect(frame_size * 2 * (i+4), frame_size * 6, frame_size * 2, frame_size);
			Skill skill8(skill_8, data);
			skill_manager_->AddSkill(skill8);
		}

		if (framenum > 10)
		{
			sprite.setOrigin(sf::Vector2f(frame_size*3.0f / 2.0f, frame_size));
			if (direct == 1)
				sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum%11), frame_size * 27, frame_size * 3, frame_size ));
			else
				sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum % 11+ 1), frame_size * 27, -frame_size * 3, frame_size ));
			return;
		}
		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * framenum , frame_size * 24, frame_size * 3, frame_size * 3));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum + 1), frame_size * 24, -frame_size * 3, frame_size * 3));
	}


	void Zero::Dash_Attack()
	{
		sprite.setOrigin(frame_size * 3.0f / 2.0f, frame_size );
		keylock = true;
		int num_of_frame = 11;
		float frame = 1.0f / 30.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}

		if (framenum == 3 && !using_skill)
		{
			using_skill = true;
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 200, 180);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x , sprite.getPosition().y - 100.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 200.0f, sprite.getPosition().y - 100.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = frame*4.0f;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}
		if (framenum >= num_of_frame)
		{
			keylock = false;
			player_state = new Standing_State((Player*)this);
			sprite.setOrigin(frame_size/2.0f, frame_size );
			return;
		}

		if (direct == 1)
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * framenum, frame_size * 18, frame_size * 3, frame_size ));
		else
			sprite.setTextureRect(sf::IntRect(frame_size * 3 * (framenum + 1), frame_size * 18, -frame_size * 3, frame_size ));
	}

	void Zero::Dash_Special_Attack()
	{
		float frame = 1.0/30.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		if (!sf::Keyboard::isKeyPressed(key[key_num]["dash"]))
			framenum = std::max(6, framenum);
		
		if (framenum>=6)
		{
			//after dashing attack
			
			sprite.setOrigin(frame_size / 2.0f, frame_size);
			if (framenum >= 9)
			{
				player_state = new Standing_State((Player*)this);
				return;
			}
			if (direct == 1)
				sprite.setTextureRect(sf::IntRect(frame_size * (framenum), frame_size * 11, frame_size, frame_size));
			else
				sprite.setTextureRect(sf::IntRect(frame_size * (framenum), frame_size * 11, -frame_size, frame_size));
				
			
		}
		else
		{
			//dashing
			framenum = framenum % 3;
			sprite.setOrigin(frame_size*3.0f / 2.0f, frame_size);
			Skill_data skill_;
			skill_.orgin = sf::Vector2f(0.0f, 0.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.rect[0] = sf::IntRect(0, 0, 110, 30);
			if (direct == 1)
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x+90.0f, sprite.getPosition().y - 50.0f);

			}
			else
			{
				skill_.pos = sf::Vector2f(sprite.getPosition().x - 200.0f, sprite.getPosition().y - 50.0f);

			}
			skill_.player = status.player_num;
			skill_.damage = 70.0f;
			skill_.texture = "Saber";
			skill_.destroyable = false;
			skill_.invisible = true;
			skill_.one_animation_skill = true;
			skill_.frame_time = 1.0f/60.0f;
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
		}
			if (direct == 1)
			{
				sprite.setTextureRect(sf::IntRect(10*frame_size+frame_size *3* framenum, frame_size * 11, frame_size*3, frame_size));
				sprite.move(velocity_x*dt_);
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(10*frame_size+frame_size *3* (framenum + 1), frame_size * 11, -frame_size*3, frame_size));
				sprite.move(-velocity_x * dt_);
			}

		
		
	}

	void Zero::Wall_slide()
	{
		sprite.setOrigin(frame_size / 2.0f, frame_size);
		float frame = 1 / 30.0f;
		
		// jump from wall
		
		if (framenum >= 3 )
		{
			frame = 1 / 20.0f;
			while (clock >= frame)
			{
				clock -= frame;
				framenum++;
			}
			if (sprite.getPosition().x <= 500.0f)
			{
				sprite.setTextureRect(sf::IntRect(frame_size * std::min(framenum, 5), frame_size * 13, frame_size, frame_size));
				sprite.move((velocity_x / 2.0f + velocity_y)*dt_);
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(frame_size * (std::min(framenum, 5)+1), frame_size * 13, -frame_size, frame_size));
				sprite.move((-velocity_x / 2.5f + velocity_y)*dt_);
			}
			sprite.setPosition(sprite.getPosition().x, std::max(Ceiling, sprite.getPosition().y));
			if (framenum == 8)
			{
				player_state = new Second_Jump_State((Player*)this);
				return;
			}
			return;
		}


		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		} 
		  framenum = 2;
		sliding = true;

		//fall from wall
		if (!sf::Keyboard::isKeyPressed(key[key_num]["left"]) && (sprite.getPosition().x <= 500.0f))
		{
			direct = 1;
			sprite.move(3.0f, 0.0f);
			player_state = new Falling_State((Player*)this);
			velocity_y = velocityy;
			return;
		}
		if (!sf::Keyboard::isKeyPressed(key[key_num]["right"]) && (sprite.getPosition().x >= 500.0f))
		{
			direct = 0;
			sprite.move(-3.0f, 0.0f);
			player_state = new Falling_State((Player*)this);
			velocity_y = velocityy;
			return;
		}

		if (sprite.getPosition().y >= Ground)
		{
			
			on_air = false;		
			player_state = new Standing_State((Player*)this);
			return;
		}

		if (sf::Keyboard::isKeyPressed(key[key_num]["jump"])) framenum = 3;
		if (sprite.getPosition().x <=500.0f)
		    sprite.setTextureRect(sf::IntRect(frame_size * framenum, frame_size * 13, frame_size, frame_size));
		else 
			sprite.setTextureRect(sf::IntRect(frame_size * (framenum+1), frame_size * 13, -frame_size, frame_size));
		sprite.move(-velocity_y *0.25f* dt_);
		
	}

	void Zero::Second_Jump()
	{
		key_lock.jump_lock = 1.0f;
		on_air = true;
		if (velocityx != velocity_x)
		{
			player_state = new Falling_State((Player*)this);
			return;
		}
		sprite.setOrigin(frame_size / 2.0f, frame_size);
		float frame = 1 / 45.0f;
		if (framenum == 0)
		{
			
			time = 0;
			set_off_y = sprite.getPosition().y;
			
		}
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		
		if (set_off_y - sprite.getPosition().y >= Max_height || sprite.getPosition().y <= Ceiling)
		{
			player_state = new Falling_State((Player*)this);
			return;
		}

		//caculate sprite position
		if (sf::Keyboard::isKeyPressed(key[key_num]["left"])) sprite.move(-velocity_x * dt_);
		if (sf::Keyboard::isKeyPressed(key[key_num]["right"])) sprite.move(velocity_x * dt_);
		time += dt_;
		velocity_y.y = velocityy.y + Gravity * time;
		sprite.move(velocity_y*dt_);

		if (framenum > 0) framenum = (framenum % 3) + 1;





		if (air_attack) clock1 += dt_;
		if ((sf::Keyboard::isKeyPressed(key[key_num]["attack"])) && (key_lock.attack_lock <= 0.0f) && (!air_attack)) {

			framenum_air_attack = 0;
			air_attack = true;
			key_lock.attack_lock = 0.5;
			clock1 = 0.0f;
		}
		if (air_attack)
		{
			On_air_attack();
			return;
		}
		if (direct == 1) sprite.setTextureRect(sf::IntRect(frame_size * (framenum+1), frame_size * 8, frame_size, frame_size));
		else sprite.setTextureRect(sf::IntRect(frame_size * (framenum + 1+1), frame_size * 8, -frame_size, frame_size));

	}

	void Zero::Giga_Attack()
	{
		/*float frame = 1.0f / 30.0f;
		if (framenum < 24) frame = 1 / 60.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		keylock = true;
		
		if (0 <= framenum && framenum < 16) sprite.setOrigin(frame_size*3.0f / 2.0f, frame_size);
		if (16 <= framenum && framenum < 24) sprite.setOrigin(frame_size*3.0f / 2.0f, frame_size*2.0f);
		if (framenum >= 24 && circle <= 5)
		{
			circle++; 
			framenum = 0;
		}
		if (24 <= framenum && framenum < 36) sprite.setOrigin(frame_size/2.0f, frame_size);
		if (36 <= framenum && framenum < 58) sprite.setOrigin(frame_size / 2.0f, frame_size*3.0f);
		if (framenum >= 58) sprite.setOrigin(frame_size / 2.0f, frame_size*2.0f);
		if (framenum == 30) sprite.setPosition(200.0f, Ground);
		sprite.setTextureRect(Giga_frame[framenum]);
		
		if (0 <= framenum && framenum < 24 && (framenum%8) >= 2)
		{
			giga_effect = true;
			Giga_sprite.setOrigin(sf::Vector2f(0.0f, frame_size*2.0f));
			Giga_sprite.setPosition(sprite.getPosition() + sf::Vector2f(150.0f, 0.0f));
			Giga_sprite.setTextureRect(sf::IntRect(framenum%8*2*frame_size,0,frame_size*2,frame_size*2));
			data->window.draw(Giga_sprite);
		}
		else giga_effect = false;
		if (framenum >= 58 && !using_skill)
		{
			Skill_data skill_;

			skill_.orgin = sf::Vector2f(0.0f, 180.0f*3.0f);
			skill_.rect = new sf::IntRect[1];
			skill_.pos = sprite.getPosition();
			skill_.vector = sf::Vector2f(1000.0f, 0.0f);
			skill_.rect[0] = sf::IntRect(0, frame_size * 15, frame_size, frame_size*3);
			skill_.texture = "Zero_skill";
			skill_.rect_num = 1;
			Skill skill(skill_, data);
			skill_manager_->AddSkill(skill);
			using_skill = true;
		}
		
		if (framenum > 68)
		{
			keylock = false;
			sprite.setOrigin(frame_size / 2.0f, frame_size);
			player_state = new Standing_State((Player*)this);
			return;
		}
		*/
		
		float frame = 1.0f / 30.0f;
		while (clock >= frame)
		{
			clock -= frame;
			framenum++;
		}
		keylock = true;

		if (framenum > 4)
		{
			sprite.setOrigin(frame_size / 2.0f, frame_size*2.0f);
			maverick_zero_mode = true;
			sprite.setTextureRect(sf::IntRect((11 + framenum % 7)*frame_size, frame_size * 6, frame_size, frame_size * 2));

		}
		else
			sprite.setTextureRect(sf::IntRect((5 + framenum )*frame_size, frame_size * 7, frame_size, frame_size ));
		if (framenum >= 30)
		{
			keylock = false;
			player_state = new Standing_State((Player*)this);
			return;
		}

	}
}