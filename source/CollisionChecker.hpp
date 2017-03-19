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
	class CollisionChecker final
	{
	public:
		CollisionChecker()
		{}

		bool AddBoxCollider( std::shared_ptr<BoxCollider> collider );

		void Update( seconds_t dt );

	private:
		std::vector<std::weak_ptr<BoxCollider>> colliders;

	private:
		void removeUnusedEntities();

		bool collidedLeft( const sf::FloatRect& a, const sf::FloatRect& aOld, const sf::FloatRect& b );
		bool collidedRight( const sf::FloatRect& a, const sf::FloatRect& aOld, const sf::FloatRect& b );
		bool collidedDown( const sf::FloatRect& a, /*const sf::FloatRect& aOld,*/ const sf::FloatRect& b );
		bool collidedTop( const sf::FloatRect& a, const sf::FloatRect& aOld, const sf::FloatRect& b );

		collisionSide_t getCollisionSide( const sf::FloatRect& collAupdated, const sf::FloatRect& collA, const sf::FloatRect& collB );
		void resolveCollision( std::weak_ptr<BoxCollider> collA, std::weak_ptr<BoxCollider> collB, const collisionSide_t collAside );
	};
}
