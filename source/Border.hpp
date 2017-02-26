/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

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

		void SetPosition( const sf::Vector2f& pos ) override { this->position = pos; this->rectangle.left = this->position.x; this->rectangle.top = this->position.y; }
		void Draw( sf::RenderTarget& target ) override;
	};
}

