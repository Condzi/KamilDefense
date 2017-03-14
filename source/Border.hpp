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
	class Border final :
		public BoxCollider,
		public Entity
	{
	public:
		Border() :
			BoxCollider( this )
		{}

		void SetPosition( const sf::Vector2f& pos ) override;
		void Draw( sf::RenderTarget& target ) override;
	};
}

