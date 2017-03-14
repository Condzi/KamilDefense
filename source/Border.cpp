/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Border.hpp"

namespace kd
{
	void Border::SetPosition( const sf::Vector2f & pos )
	{
		this->position = pos;
		this->rectangle.left = this->position.x;
		this->rectangle.top = this->position.y;
	}

	void Border::Draw( sf::RenderTarget& target )
	{
		if ( !DEBUG_DRAW_BORDERS )
			return;

		sf::RectangleShape shape;
		shape.setPosition( rectangle.left, rectangle.top );
		shape.setSize( { rectangle.width, rectangle.height } );
		shape.setFillColor( sf::Color::Transparent );
		shape.setOutlineThickness( 2.0f );
		shape.setOutlineColor( sf::Color::Red );

		target.draw( shape );
	}
}