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
			cgf::Logger::Log( "Cannot add collider to PhysicsChecker - collider pointer is not assigned", cgf::Logger::ERROR );
		}

		for ( auto ptr : this->colliders )
			if ( ptr.lock() == collider )
			{
				cgf::Logger::Log( "Cannot add collider to PhysicsChecker - found pointer pointing to same collider", cgf::Logger::ERROR );
				return false;
			}

		this->colliders.push_back( collider );

		cgf::Logger::Log( "Added collider to PhysicsChecker, total colliders: " + std::to_string( colliders.size() ) );

		return true;
	}

	void PhysicsChecker::Update( seconds_t dt )
	{
		this->removeUnusedEntities();

		for ( size_t i = 0; i < this->colliders.size(); i++ )
			for ( size_t j = 0; j < this->colliders.size(); j++ )
			{
				if ( i == j ||
					colliders[j].lock()->parentPointer->GetType() == entityID_t::BORDER )
					continue;

				sf::FloatRect& collA = colliders[j].lock()->rectangle;
				sf::FloatRect& collB = colliders[i].lock()->rectangle;
				sf::FloatRect collAupdated = collA;
				collAupdated.left += colliders[j].lock()->velocity.x * dt;
				collAupdated.top += colliders[j].lock()->velocity.y * dt;

				if ( !collAupdated.intersects( collB ) )
					continue;

				resolveCollision( colliders[j], colliders[i], getCollisionSide( collAupdated, collA, collB ) );
			}
	}


	void PhysicsChecker::removeUnusedEntities()
	{
		for ( auto it = this->colliders.begin(); it != this->colliders.end();)
		{
			if ( it->expired() || it->lock()->parentPointer->IsWishingDelete() )
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

	collisionSide_t PhysicsChecker::getCollisionSide( const sf::FloatRect& collAupdated, const sf::FloatRect& collA, const sf::FloatRect& collB )
	{
		collisionSide_t collAside = None;

		if ( collidedLeft( collAupdated, collA, collB ) )
			collAside = Left;
		else if ( collidedRight( collAupdated, collA, collB ) )
			collAside = Right;
		else if ( collidedTop( collAupdated, collA, collB ) )
			collAside = Top;
		else if ( collidedDown( collAupdated, collA, collB ) )
			collAside = Down;

		return collAside;
	}

	void PhysicsChecker::resolveCollision( std::weak_ptr<BoxCollider> collA, std::weak_ptr<BoxCollider> collB, collisionSide_t collAside )
	{
		entityID_t typeA = collA.lock()->parentPointer->GetType();
		entityID_t typeB = collB.lock()->parentPointer->GetType();

		if ( typeA == entityID_t::PLAYER )
		{
			if ( typeB == entityID_t::BORDER )
				CollisionSolver::EntityEntity( collA, collB, collAside );
		} else if ( typeA == entityID_t::ENEMY )
		{
			if ( typeB == entityID_t::BORDER )
				CollisionSolver::EnemyEntity( collA, collB, collAside );
			else if ( typeB == entityID_t::PLAYER )
				CollisionSolver::EnemyPlayer( collA, collB, collAside );
		} else if ( typeA == entityID_t::BULLET_PLAYER )
		{
			if ( typeB == entityID_t::BORDER )
				CollisionSolver::BulletEntity( collA );
			else if ( typeB == entityID_t::ENEMY )
				CollisionSolver::BulletEnemy( collA, collB );
			else if ( typeB == entityID_t::BULLET_ENEMY )
				CollisionSolver::BulletBullet( collA, collB );
		} else if ( typeA == entityID_t::BULLET_ENEMY )
		{
			if ( typeB == entityID_t::BORDER )
				CollisionSolver::BulletEntity( collA );
			else if ( typeB == entityID_t::PLAYER )
				CollisionSolver::BulletPlayer( collA, collB );
		}
	}
}