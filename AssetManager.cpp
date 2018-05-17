#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

namespace frost
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		//fuck this shitty code 
		/*
		sf::Texture tex;
		if (tex.loadFromFile(fileName))
		{

			this->_textures[name] = tex;	
		}
		*/

		if (!this->_textures[name].loadFromFile(fileName))
			std::cout << fileName << " 's not available";
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
}