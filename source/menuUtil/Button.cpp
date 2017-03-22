/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Button.hpp"

namespace kd
{
	void Button::SetShapeSize( const sf::Vector2f& sz )
	{
		this->shape.setSize( sz );
	}

	void Button::SetPosition( const sf::Vector2f& pos )
	{
		this->position = pos;
		this->shape.setPosition( pos );
		this->text.setPosition( pos.x, pos.y - pos.y / 20);
	}

	void Button::SetTextString( const std::string &t )
	{
		this->text.setString( t );
	}

	void Button::SetTextSize( uint8_t size )
	{
		this->text.setCharacterSize( size );
	}

	void Button::SetTextFont( std::weak_ptr<sf::Font> font )
	{
		this->text.setFont( *font.lock() );
	}

	void Button::SetOutline( float thickness, const sf::Color& colorOutside, const sf::Color& colorInside )
	{
		this->shape.setOutlineThickness( thickness );
		this->shape.setOutlineColor( colorOutside );
		this->shape.setFillColor( colorInside );
	}

	sf::FloatRect Button::GetRectangle()
	{
		return this->shape.getGlobalBounds();
	}

	void Button::Draw( sf::RenderTarget& target )
	{
		target.draw( shape );
		target.draw( text );
	}
}