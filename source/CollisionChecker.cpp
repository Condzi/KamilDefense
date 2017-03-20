/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "CollisionChecker.hpp"

namespace kd
{
	bool CollisionChecker::AddBoxCollider( std::shared_ptr<BoxCollider> collider )
	{
		if ( !collider )
		{
			cgf::Logger::Log( "Cannot add collider to CollisionChecker - collider pointer is not assigned", cgf::Logger::ERROR );
		}

		for ( auto ptr : this->colliders )
			if ( ptr.lock() == collider )
			{
				cgf::Logger::Log( "Cannot add collider to CollisionChecker - found pointer pointing to same collider", cgf::Logger::ERROR );
				return false;
			}

		this->colliders.push_back( collider );

		cgf::Logger::Log( "Added collider to CollisionChecker, total colliders: " + std::to_string( colliders.size() ), cgf::Logger::INFO, cgf::Logger::CONSOLE );

		return true;
	}

	void CollisionChecker::Update( seconds_t dt )
	{
		this->removeUnusedEntities();

		for ( size_t i = 0; i < this->colliders.size(); i++ )
			for ( size_t j = 0; j < this->colliders.size(); j++ )
			{
				if ( i == j ||
					this->colliders[j].lock()->parentPointer->GetType() == entityID_t::BORDER )
					continue;

				if ( ( this->colliders[i].lock()->parentPointer->GetType() == entityID_t::BULLET_ENEMY && this->colliders[j].lock()->parentPointer->GetType() == entityID_t::ENEMY ) )
					continue;

				sf::FloatRect& collA = this->colliders[j].lock()->rectangle;
				sf::FloatRect& collB = this->colliders[i].lock()->rectangle;
				sf::FloatRect collAupdated = collA;
				collAupdated.left += this->colliders[j].lock()->velocity.x * dt;
				collAupdated.top += this->colliders[j].lock()->velocity.y * dt;

				if ( !collAupdated.intersects( collB ) )
					continue;

				this->resolveCollision( this->colliders[j], this->colliders[i], getCollisionSide( collAupdated, collA, collB ) );
			}
	}


	void CollisionChecker::removeUnusedEntities()
	{
		for ( auto it = this->colliders.begin(); it != this->colliders.end();)
		{
			if ( it->expired() || it->lock()->parentPointer->IsWishingDelete() )
				it = this->colliders.erase( it );
			else
				it++;
		}
	}

	bool CollisionChecker::collidedLeft( const sf::FloatRect& a, const sf::FloatRect& aOld, const sf::FloatRect& b )
	{
		return aOld.left + aOld.width <= b.left &&
			a.left + a.width >= b.left;
	}

	bool CollisionChecker::collidedRight( const sf::FloatRect& a, const sf::FloatRect& aOld, const sf::FloatRect& b )
	{
		return aOld.left >= b.left + b.width &&
			a.left <= b.left + b.width;
	}

	bool CollisionChecker::collidedDown( const sf::FloatRect& a, /*const sf::FloatRect& aOld,*/ const sf::FloatRect& b )
	{
		// commented for continous checking 
		return //aOld.top + aOld.height <= b.top &&
			a.top + a.height >= b.top;
	}

	bool CollisionChecker::collidedTop( const sf::FloatRect& a, const sf::FloatRect& aOld, const sf::FloatRect& b )
	{
		return aOld.top >= b.top + b.height &&
			a.top <= b.top + b.height;
	}

	collisionSide_t CollisionChecker::getCollisionSide( const sf::FloatRect& collAupdated, const sf::FloatRect& collA, const sf::FloatRect& collB )
	{
		collisionSide_t collAside = collisionSide_t::NONE;

		if ( collidedLeft( collAupdated, collA, collB ) )
			collAside = collisionSide_t::LEFT;
		else if ( collidedRight( collAupdated, collA, collB ) )
			collAside = collisionSide_t::RIGHT;
		else if ( collidedTop( collAupdated, collA, collB ) )
			collAside = collisionSide_t::TOP;
		else if ( collidedDown( collAupdated, /*collA,*/ collB ) )
			collAside = collisionSide_t::DOWN;

		return collAside;
	}

	void CollisionChecker::resolveCollision( std::weak_ptr<BoxCollider> collA, std::weak_ptr<BoxCollider> collB, const collisionSide_t collAside )
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
			else if ( typeB == entityID_t::PLAYER_BASE )
				CollisionSolver::EnemyBase( collA, collB );
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