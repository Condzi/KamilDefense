/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "BoxCollider.hpp"
#include "Entity.hpp"
#include "GameConfig.hpp"

namespace kd
{
	class Border final : public Entity, public BoxCollider
	{
	public:
		Border() : BoxCollider( this )
		{}

		void Update( seconds_t dt ) override { this->rectangle.left = this->position.x; this->rectangle.top = this->position.y; }
		void Draw( sf::RenderTarget& target ) override
		{
			if ( !DEBUG_DRAW_BORDERS )
				return;

			sf::RectangleShape shape;
			shape.setPosition( rectangle.left, rectangle.top );
			shape.setSize( { rectangle.width, rectangle.height } );
			shape.setFillColor( sf::Color::Transparent );
			shape.setOutlineThickness( 2.f );
			shape.setOutlineColor( sf::Color::Red );

			target.draw( shape );
		}

	};
}

