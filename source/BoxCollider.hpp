/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace kd
{
	class Entity;

	class BoxCollider
	{
		friend class PhysicsChecker;
		friend class CollisionSolver;

	public:
		sf::FloatRect rectangle;
		sf::Vector2f velocity;

	public:
		BoxCollider( Entity* parentPtr ) :
			rectangle( 0.0f, 0.0f, 0.0f, 0.0f ),
			velocity( 0.0f, 0.0f ),
			parentPointer( parentPtr ),
			grounded( false )
		{}

		virtual ~BoxCollider() = default;

	protected:
		bool grounded;

	private:
		Entity* parentPointer;
	};
}
