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
		this->updateTextPosition = true;
	}

	void Button::SetTextString( const std::string &t )
	{
		this->text.setString( t );
		this->updateTextPosition = true;
	}

	void Button::SetTextSize( uint8_t size )
	{
		this->text.setCharacterSize( size );
		this->updateTextPosition = true;
	}

	void Button::SetTextFont( std::weak_ptr<sf::Font> font )
	{
		this->text.setFont( *font.lock() );
		this->updateTextPosition = true;
	}

	void Button::SetOutline( float thickness, const sf::Color& colorOutside, const sf::Color& colorInside )
	{
		this->shape.setOutlineThickness( thickness );
		this->shape.setOutlineColor( colorOutside );
		this->shape.setFillColor( colorInside );
		// Inversing color
		uint8_t rgbMax = UINT8_MAX;
		this->text.setOutlineColor( { 
			uint8_t( rgbMax - this->text.getFillColor().r ), 
			uint8_t( rgbMax - this->text.getFillColor().g ), 
			uint8_t( rgbMax - this->text.getFillColor().b ) 
		} );
		this->text.setOutlineThickness( thickness / 4 );
	}

	sf::FloatRect Button::GetRectangle()
	{
		return this->shape.getGlobalBounds();
	}

	void Button::Update( seconds_t dt )
	{
		if ( this->updateTextPosition )
		{
			this->text.setPosition( this->position.x, this->position.y - this->text.getGlobalBounds().height );
			this->updateTextPosition = false;
		}
	}

	void Button::Draw( sf::RenderTarget& target )
	{
		target.draw( shape );
		target.draw( text );
	}
}