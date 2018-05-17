#include "Character.hpp"

namespace frost
{
	
	void Character::SetUpKeyMapping()
	{
		key[2]["right"] = sf::Keyboard::Right;
		key[2]["left"] = sf::Keyboard::Left;
		//key[1]["up"] = sf::Keyboard::Up;
		key[2]["down"] = sf::Keyboard::Down;
		key[2]["attack"] = sf::Keyboard::Period;
		key[2]["jump"] = sf::Keyboard::Up;
		//key[1]["jump"] = sf::Keyboard::Period;
		key[2]["dash"] = sf::Keyboard::Comma;
		key[2]["special_attack"] = sf::Keyboard::Slash;
		key[2]["change_attribute"] = sf::Keyboard::L;
		//key[1]["giga_attack"] = sf::Keyboard::B;

		key[1]["right"] = sf::Keyboard::D;
		key[1]["left"] = sf::Keyboard::A;
		//key[2]["up"] = sf::Keyboard::W;
		key[1]["down"] = sf::Keyboard::S;
		key[1]["attack"] = sf::Keyboard::G;
		key[1]["jump"] = sf::Keyboard::W;
		//key[2]["jump"] = sf::Keyboard::G;
		key[1]["dash"] = sf::Keyboard::F;
		key[1]["special_attack"] = sf::Keyboard::H;
		key[1]["change_attribute"] = sf::Keyboard::R;
		//key[2]["giga_attack"] = sf::Keyboard::R;


	}

	bool Character::End()
	{
		return ending;
	}
	void Character::SetupTexture()
	{
		data->assets.LoadTexture("Effect", "Resources/res/effect.png");
		data->assets.LoadTexture("Zero_skill", "Resources/res/Zero_skill.png");
		data->assets.LoadTexture("Saber", "Resources/res/saber.png");
		data->assets.LoadTexture("Zero", "Resources/res/Zero.png");
		data->assets.LoadTexture("Zero_Black", "Resources/res/Zero_black.png");
	}
	void Character::Init(GameDataRef data__,std::string name_1,std::string name_2)
	{
		data = data__;
		
		SetUpKeyMapping();
		SetupTexture();

		skill_manager = new Skill_Manager(data);

		player_1 = new Zero(data,key,skill_manager,1,name_1);
		
		hud_1.Setup(player_1->Get_status(),data,1);

		player_2 = new Zero(data, key, skill_manager, 2,name_2);

		hud_2.Setup(player_2->Get_status(), data,2);
		
		
		
	}
	Player *Character::GetPlayer_1()
	{
		return player_1;
	}
	Player *Character::GetPlayer_2()
	{
		return player_2;
	}
	void Character::HandleInput()
	{
		
		player_1->HandleInput();
		player_2->HandleInput();
		//std::cout << "ok";

	}
	void Character::Update(float dt)
	{
		
		player_1->Update(dt);
		player_2->Update(dt);
		skill_manager->Update(dt);
		skill_manager->Skill_Hit(player_1,player_1->Get_Sprite());
		skill_manager->Skill_Hit(player_2, player_2->Get_Sprite());
		hud_1.Update(dt);
		hud_2.Update(dt);
		if (player_1->Get_status()->Health <= 0.0f)
		{
			ending = true;
			data->machine.AddState(StateRef(new Gameover_State(data, "Player 1 Win")));
		}
		if (player_2->Get_status()->Health <= 0.0f)
		{
			ending = true;
			data->machine.AddState(StateRef(new Gameover_State(data, "Player 2 Win")));
		}
		
	}
	void Character::Draw()
	{
		player_1->Draw();
		player_2->Draw();
		skill_manager->Draw();
		hud_1.Draw();
		hud_2.Draw();


	}
}