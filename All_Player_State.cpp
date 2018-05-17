#include "All_Player_State.hpp"

namespace frost
{
	Standing_State::Standing_State(Player *player_) : player(player_)
	{
		player->Reset();
	}
	Player_State* Standing_State::HandleInput(Key *key, int key_num)
	{
		if (sf::Keyboard::isKeyPressed(key[key_num]["left"]) && player->Get_Key_lock().left_lock==0.0f)
			return new Running_State(player);
		if (sf::Keyboard::isKeyPressed(key[key_num]["right"]) && player->Get_Key_lock().right_lock == 0.0f)
			return new Running_State(player);
		//if (sf::Keyboard::isKeyPressed(key[key_num]["giga_attack"])) return new Giga_Attack_State(player);
		if (sf::Keyboard::isKeyPressed(key[key_num]["jump"])) return new Jumping_State(player);
		if (sf::Keyboard::isKeyPressed(key[key_num]["dash"])&& (player->Get_Key_lock().dash_lock<=0.0f)) return new Dashing_State(player);
		if (sf::Keyboard::isKeyPressed(key[key_num]["down"])) return new Ducking_State(player);
		if (sf::Keyboard::isKeyPressed(key[key_num]["attack"])) return new Attacking_State(player);
		if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"]))	return new Special_Attack_State(player);
		return this;
	}
	void Standing_State::Update()
	{
		player->Stand();
	}

	 Dashing_State::Dashing_State(Player *player_) : player(player_)
	{
		 player->Reset();
	}
	 Player_State* Dashing_State::HandleInput(Key *key, int key_num)
	 {
		 if (sf::Keyboard::isKeyPressed(key[key_num]["dash"]))
		 {
			 if (sf::Keyboard::isKeyPressed(key[key_num]["jump"])) return new Jumping_State(player);
			 if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"]))
				 return new Dashing_Special_attack_State(player);
			 
			 if (sf::Keyboard::isKeyPressed(key[key_num]["attack"]) && player->Get_status()->type != x) return new Dashing_Attack_State(player);
		 }
		 return this;
		 
	 }
	 void Dashing_State::Update()
	 {
		 player->Dash();
	 }

	 Jumping_State::Jumping_State(Player *player_) : player(player_)
	 {
		 player->Reset();
	 }
	 Player_State* Jumping_State::HandleInput(Key *key, int key_num)
	 {
		 if (sf::Keyboard::isKeyPressed(key[key_num]["jump"]))
		 {
			 if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"])) return new On_air_Special_attack_State(player);
			 return this;
		 }
		 return new Falling_State(player);
	 }
	 void Jumping_State::Update()
	 {
		 player->Jump();
	 }

	 Ducking_State::Ducking_State(Player *player_) : player(player_)
	 {
		 player->Reset();
	 }
	 Player_State* Ducking_State::HandleInput(Key *key, int key_num)
	 {
		 if (sf::Keyboard::isKeyPressed(key[key_num]["down"]))
		 {
			 if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"])) return new Ducking_Specialattack_State(player);
			 if (sf::Keyboard::isKeyPressed(key[key_num]["attack"])) return new Ducking_Attack_State(player);
			 return this;
		 }
		 
		 else return new Standing_State(player);
	 }
	 void Ducking_State::Update()
	 {
		 player->Duck();
	 }

	 Running_State::Running_State(Player *player_) : player(player_)
	 {
		 player->Reset();
	 }
	 Player_State* Running_State::HandleInput(Key *key, int key_num)
	 {
		 if (sf::Keyboard::isKeyPressed(key[key_num]["left"]) && player->Get_Key_lock().left_lock == 1.0f)
			 return new Standing_State(player);

		 if (sf::Keyboard::isKeyPressed(key[key_num]["right"]) && player->Get_Key_lock().right_lock == 1.0f)
			 return new Standing_State(player);

		 if (sf::Keyboard::isKeyPressed(key[key_num]["left"]) || sf::Keyboard::isKeyPressed(key[key_num]["right"]))
		 { 

			 if (sf::Keyboard::isKeyPressed(key[key_num]["jump"])) return new Jumping_State(player);
			 if (sf::Keyboard::isKeyPressed(key[key_num]["dash"]) && (player->Get_Key_lock().dash_lock<=0.0f)) return new Dashing_State(player);
			 if (sf::Keyboard::isKeyPressed(key[key_num]["down"])) return new Ducking_State(player);
			 if (sf::Keyboard::isKeyPressed(key[key_num]["attack"])&& player->Get_status()->type == zero) return new Attacking_State(player);
			 //if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"]))	return new Special_Attack_State(player);
			 return this;
		 }
		 else	 
		   return new Standing_State(player);
		 
	 }
	 void Running_State::Update()
	 {
		
		 player->Run();
	 }


	 Attacking_State::Attacking_State(Player *player_) : player(player_)
	 {
		 player->Reset();
	 }
	 Player_State* Attacking_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void Attacking_State::Update()
	 {
		 player->Attack();
	 }

	 Falling_State::Falling_State(Player* player_) : player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *Falling_State::HandleInput(Key *key, int key_num)
	 {

		 if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"])) return new On_air_Special_attack_State(player);
		 if (sf::Keyboard::isKeyPressed(key[key_num]["jump"]) && player->Get_Key_lock().jump_lock == 0.0f) return new Second_Jump_State(player);
		 return this;
	 }
	 void Falling_State::Update()
	 {
		 player->Fall();
	 }

	 Special_Attack_State::Special_Attack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *Special_Attack_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void Special_Attack_State::Update()
	 {
		 player->Special_Attack();
	 }

	 Ducking_Attack_State::Ducking_Attack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *Ducking_Attack_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void Ducking_Attack_State::Update()
	 {
		 player->Duck_Attack();
	 }

	 Ducking_Specialattack_State::Ducking_Specialattack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *Ducking_Specialattack_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void Ducking_Specialattack_State::Update()
	 {
		 player->Duck_Special_Attack();
	 }

	 

	 Dashing_Attack_State::Dashing_Attack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *Dashing_Attack_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void Dashing_Attack_State::Update()
	 {
		 player->Dash_Attack();
	 }

	 On_air_Special_attack_State::On_air_Special_attack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State * On_air_Special_attack_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void  On_air_Special_attack_State::Update()
	 {
		 player->On_air_Special_attack();
	 }

	 Dashing_Special_attack_State::Dashing_Special_attack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State * Dashing_Special_attack_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void  Dashing_Special_attack_State::Update()
	 {
		 player->Dash_Special_Attack();
	 }


	 Wall_Sliding_State::Wall_Sliding_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State * Wall_Sliding_State::HandleInput(Key *key, int key_num)
	 {
		 return this;
	 }
	 void  Wall_Sliding_State::Update()
	 {
		 player->Wall_slide();
	 }
	 Second_Jump_State::Second_Jump_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *  Second_Jump_State::HandleInput(Key *key, int key_num)
	 {
		 
		 if (sf::Keyboard::isKeyPressed(key[key_num]["jump"]))
		 {
			 if (sf::Keyboard::isKeyPressed(key[key_num]["special_attack"])) return new On_air_Special_attack_State(player);
			 return this;
		 }
		 std::cout << "1";
		 return new Falling_State(player);
	 }
	 void   Second_Jump_State::Update()
	 {
		 player->Second_Jump();
	 }

	 Giga_Attack_State::Giga_Attack_State(Player *player_) :player(player_)
	 {
		 player->Reset();
	 }
	 Player_State *   Giga_Attack_State::HandleInput(Key *key, int key_num)
	 {

		 return this;
	 }
	 void   Giga_Attack_State::Update()
	 {
		 player->Giga_Attack();
	 }
}