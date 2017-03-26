/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "MissileManager.hpp"

namespace kd
{
	bool MissileManager::initialized;
	std::vector<std::weak_ptr<Missile>> MissileManager::missiles;
	CollisionChecker* MissileManager::collisionCheckerPtr;
	std::vector<std::shared_ptr<Entity>>* MissileManager::entitiesPtr;

	void MissileManager::Initialize( CollisionChecker* physicCh, std::vector<std::shared_ptr<Entity>>* entPtr )
	{
		MissileManager::initialized = true;

		if ( !physicCh )
			MissileManager::initialized = false;
		else
			MissileManager::collisionCheckerPtr = physicCh;

		if ( !entPtr )
			MissileManager::initialized = false;
		else
			MissileManager::entitiesPtr = entPtr;

		if ( !initialized )
			cgf::Logger::Log( "Cannot initialize Missile Manager, unassigned collisionCheckerPtr or entitiesPtr", cgf::Logger::ERROR );
		else
			cgf::Logger::Log( "Missile Manager initialized!" );
	}

	void MissileManager::Shutdown()
	{
		if ( !MissileManager::initialized )
			cgf::Logger::Log( "Trying to shutdown unitialized missile manager...", cgf::Logger::WARNING );

		for ( auto ptr : MissileManager::missiles )
			if ( !ptr.expired() )
				ptr.lock()->SetWishDelete( true );

		MissileManager::missiles.clear();
		MissileManager::initialized = false;
		cgf::Logger::Log( "Missile Manager shutdown!" );
	}

	void MissileManager::AddMissile( std::shared_ptr<Missile> missile )
	{
		if ( !MissileManager::initialized )
			return;

		missile->SetDrawLayer( 1 );
		MissileManager::missiles.push_back( missile );
		MissileManager::collisionCheckerPtr->AddBoxCollider( missile );
		MissileManager::entitiesPtr->push_back( missile );
	}

	void MissileManager::Update( seconds_t dt )
	{
		if ( !MissileManager::initialized )
			return;

		MissileManager::removeUnusedMissiles();
	}

	void MissileManager::removeUnusedMissiles()
	{
		for ( auto ptr : MissileManager::missiles )
			if ( !MissileManager::isInWindowBounds( ( ptr.lock()->GetPosition() ) ) )
				ptr.lock()->SetWishDelete( true );

		for ( auto it = MissileManager::missiles.begin(); it != MissileManager::missiles.end();)
		{
			if ( ( *it ).expired() ||
				( *it ).lock()->IsWishingDelete() )
				it = MissileManager::missiles.erase( it );
			else
				it++;
		}
	}

	bool MissileManager::isInWindowBounds( const sf::Vector2f& pos )
	{
		return pos.x > SETTINGS.GLOBAL.WINDOW_SIZE_X || pos.y > SETTINGS.GLOBAL.WINDOW_SIZE_Y ||
			pos.x < 0 || pos.y > 0;
	}
}