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

		void SetTexture( std::shared_ptr<sf::Texture> tex )
		{
			if ( !tex )
				cgf::Logger::log( "Background texture is not assigned", cgf::Logger::WARNING );
			else
			{
				texture = tex;
				sprite.setTexture( *texture );
				sprite.scale( 2.0f, 2.0f );
				sprite.scale( SCALE, SCALE );
			}
		}

		void Draw( sf::RenderTarget& target ) override
		{
			if ( !texture )
			{
				cgf::Logger::log( "Background texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
				return;
			}

			target.draw( sprite );
		}

	private:
		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite;
	};
}

