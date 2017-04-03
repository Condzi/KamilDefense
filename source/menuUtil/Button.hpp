/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "entities/Enemy.hpp"
#include "entities/Drawable.hpp"

namespace kd
{
	class Button final :
		public Drawable,
		public Entity
	{
	public:
		Button() :
			updateTextPosition( false )
		{}

		sf::FloatRect GetRectangle();

		void SetShapeSize( const sf::Vector2f& sz );
		void SetPosition( const sf::Vector2f& pos ) override;
		void SetTextString( const std::string& t );
		void SetTextSize( uint8_t size );
		void SetTextFont( std::weak_ptr<sf::Font> font );
		void SetOutline( float thickness, const sf::Color& colorOutside, const sf::Color& colorInside );
		void SetTexture( std::weak_ptr<sf::Texture> t ) override
		{
			cgf::Logger::Log( "You called " + std::string( SHOW_REAL_NAME( *this ) ) + "::SetTexture method - you shouldn't, it doesn't have texture", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		}
		
		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target );

	private:
		bool updateTextPosition;
		sf::RectangleShape shape;
		sf::Text text;
	};
}
