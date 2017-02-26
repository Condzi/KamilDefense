/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Logger.hpp>

#include "Entity.hpp"
#include "GameConfig.hpp"

namespace kd
{
	class Background final : public Entity
	{
	public:
		Background()
		{}

		void SetTexture( std::shared_ptr<sf::Texture> tex );
		void Draw( sf::RenderTarget& target ) override;

	private:
		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite;
	};
}

