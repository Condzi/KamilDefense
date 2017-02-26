/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PhysicsChecker.hpp"

namespace kd
{
	bool PhysicsChecker::AddBoxCollider( std::shared_ptr<BoxCollider> collider )
	{
		if ( !collider )
		{
			cgf::Logger::log( "Cannot add collider to PhysicsChecker - collider pointer is not assigned", cgf::Logger::ERROR );
		}

		for ( auto ptr : this->colliders )
			if ( ptr == collider )
			{
				cgf::Logger::log( "Cannot add collider to PhysicsChecker - found pointer pointing to same collider", cgf::Logger::ERROR );
				return false;
			}

		this->colliders.push_back( collider );

		cgf::Logger::log( "Added collider to PhysicsChecker, total colliders: " + std::to_string( colliders.size() ) );

		return true;
	}

	void PhysicsChecker::Update( seconds_t dt )
	{
		this->removeUnusedEntities();

		for ( size_t i = 0; i < this->colliders.size(); i++ )
			for ( size_t j = 0; j < this->colliders.size(); j++ )
			{
				if ( !shouldCheckForPhysics( i, j ) )
					continue;

				sf::FloatRect& collA = colliders[j]->rectangle;
				sf::FloatRect collAupdated = collA;
				collAupdated.left += colliders[j]->velocity.x * dt;
				collAupdated.top += colliders[j]->velocity.y * dt;
				sf::FloatRect& collB = colliders[i]->rectangle;

				if ( !collAupdated.intersects( collB ) )
					continue;

				collisionSide_t collAside = None;

				if ( collidedLeft( collAupdated, collA, collB ) )
					collAside = Left;
				else if ( collidedRight( collAupdated, collA, collB ) )
					collAside = Right;
				else if ( collidedTop( collAupdated, collA, collB ) )
					collAside = Top;
				else if ( collidedDown( collAupdated, collA, collB ) )
					collAside = Down;

				resolveCollision( colliders[j], colliders[i], collAside );
			}
	}


	void PhysicsChecker::removeUnusedEntities()
	{
		for ( auto it = this->colliders.begin(); it != this->colliders.end();)
		{
			if ( ( *it )->parentPointer->IsWishingDelete() )
				it = this->colliders.erase( it );
			else
				it++;
		}
	}

	bool PhysicsChecker::collidedLeft( const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b )
	{
		return a_old.left + a_old.width <= b.left &&
			a.left + a.width >= b.left;
	}

	bool PhysicsChecker::collidedRight( const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b )
	{
		return a_old.left >= b.left + b.width &&
			a.left <= b.left + b.width;
	}

	bool PhysicsChecker::collidedDown( const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b )
	{
		// commented for continous checking 
		return //a_old.top + a_old.height <= b.top &&
			a.top + a.height >= b.top;
	}

	bool PhysicsChecker::collidedTop( const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b )
	{
		return a_old.top >= b.top + b.height &&
			a.top <= b.top + b.height;
	}

	bool PhysicsChecker::shouldCheckForPhysics( size_t i, size_t j )
	{
		if ( i == j ||
			colliders[j]->parentPointer->GetType() == entityID_t::BORDER )
			return false;

		return true;
	}

	void PhysicsChecker::resolveCollision( std::shared_ptr<BoxCollider> collA, std::shared_ptr<BoxCollider> collB, collisionSide_t collAside )
	{
		entityID_t typeA = collA->parentPointer->GetType();
		entityID_t typeB = collB->parentPointer->GetType();

		if ( typeA == entityID_t::PLAYER)
		{
			if ( typeB == entityID_t::BORDER )
				CollisionSolver::EntityEntity( collA, collB, collAside );
			else if ( typeB == entityID_t::ENEMY )
				CollisionSolver::EntityEntity( collA, collB, collAside );
		} else if ( typeA == entityID_t::ENEMY )
		{
			if ( typeB == entityID_t::BORDER )
				CollisionSolver::EnemyEntity( collA, collB, collAside );
		}
	}
}