/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

#include <Logger.hpp>

#include "BoxCollider.hpp"
#include "CollisionSolver.hpp"
#include "Entity.hpp"
#include "Types.hpp"

namespace kd
{
	class PhysicChecker final
	{
	private:
		void removeUnusedEntities();

		bool collidedLeft(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b);
		bool collidedRight(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b);
		bool collidedDown(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b);
		bool collidedTop(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b);

	public:
		PhysicChecker()
		{}

		bool addBoxCollider(std::shared_ptr<BoxCollider> collider);

		void update(seconds_t dt);

	private:
		std::vector<std::shared_ptr<BoxCollider>> colliders;
	};
}
