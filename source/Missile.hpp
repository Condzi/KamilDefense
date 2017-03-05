/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "BoxCollider.hpp"
#include "Entity.hpp"

namespace kd
{
	class MissileManager;

	class Missile final :
		public Entity,
		public BoxCollider
	{
		friend class CollisionSolver;

	public:
		Missile();

		void SetPosition( const sf::Vector2f& pos );

		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target ) override;

	private:
		sf::RectangleShape shape;
	};
}
