/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "MissileManager.hpp"

namespace kd
{
	bool MissileManager::initialized;
	std::vector<std::shared_ptr<Missile>> MissileManager::missiles;
	CollisionChecker* MissileManager::collisionChecker;

	void MissileManager::Initialize( CollisionChecker* physicCh )
	{
		initialized = true;

		if ( !physicCh )
			initialized = false;
		else
			MissileManager::collisionChecker = physicCh;

		if ( !initialized )
			cgf::Logger::Log( "Cannot initialize Missile Manager, unassigned collisionChecker!", cgf::Logger::ERROR );
		else
			cgf::Logger::Log( "Missile Manager initialized!" );

	}

	void MissileManager::Shutdown()
	{
		MissileManager::missiles.clear();
		cgf::Logger::Log( "Missile Manager shutdown!" );
	}

	void MissileManager::AddMissile( std::shared_ptr<Missile> missile )
	{
		if ( !MissileManager::initialized )
			return;

		MissileManager::missiles.push_back( std::move( missile ) );
		MissileManager::collisionChecker->AddBoxCollider( MissileManager::missiles.back() );
	}

	void MissileManager::Update( seconds_t dt )
	{
		if ( !MissileManager::initialized )
			return;

		MissileManager::removeUnusedMissiles();

		for ( auto ptr : missiles )
			ptr->Update( dt );
	}

	void MissileManager::Draw( sf::RenderTarget& target )
	{
		if ( !MissileManager::initialized )
			return;

		for ( auto ptr : missiles )
			ptr->Draw( target );
	}

	void MissileManager::removeUnusedMissiles()
	{
		for ( auto it = MissileManager::missiles.begin(); it != MissileManager::missiles.end();)
		{
			if ( ( *it )->IsWishingDelete() || 
				!MissileManager::isInWindowBounds( ( *it )->GetPosition() ) )
				it = MissileManager::missiles.erase( it );
			else
				it++;
		}
	}

	bool MissileManager::isInWindowBounds( const sf::Vector2f& pos )
	{
		return pos.x > WINDOW_SIZE.x || pos.y > WINDOW_SIZE.y ||
			pos.x < 0 || pos.y > 0;
	}
}