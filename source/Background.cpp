/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Background.hpp"

namespace kd
{
	void Background::SetTexture( std::shared_ptr<sf::Texture> tex )
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

	void Background::Draw( sf::RenderTarget & target )
	{
		if ( !texture )
		{
			cgf::Logger::log( "Background texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
			return;
		}

		target.draw( sprite );
	}
}