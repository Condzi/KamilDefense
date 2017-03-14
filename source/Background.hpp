/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Logger.hpp>

#include "Drawable.hpp"
#include "Entity.hpp"
#include "GameConfig.hpp"

namespace kd
{
	class Background final :
		public Entity,
		public Drawable
	{
	public:
		Background()
		{}

		void SetTexture( std::weak_ptr<sf::Texture> tex ) override;
		void Draw( sf::RenderTarget& target ) override;

	private:
		sf::Sprite sprite;
	};
}

