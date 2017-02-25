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
		friend class PhysicChecker;
		friend class CollisionSolver;

	public:
		BoxCollider(std::shared_ptr<Entity> parentPtr) :
			rectangle(0, 0, 0, 0),
			velocity(0, 0),
			parentPointer(parentPtr),
			grounded(false)
		{}

		virtual ~BoxCollider() = default;

		sf::FloatRect rectangle;
		sf::Vector2f velocity;

	protected:
		bool grounded;

	private:
		std::shared_ptr<Entity> parentPointer;
	};
}
