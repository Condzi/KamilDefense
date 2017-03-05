/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "MissileManager.hpp"

namespace kd
{
	bool MissileManager::correctInitialization;
	std::vector<std::shared_ptr<Missile>> MissileManager::missiles;
	PhysicsChecker* MissileManager::physicChecker;

	void MissileManager::Initialize( PhysicsChecker* physicCh )
	{
		correctInitialization = true;

		if ( !physicCh )
			correctInitialization = false;
		else
			MissileManager::physicChecker = physicCh;

		if ( !correctInitialization )
			cgf::Logger::Log( "Cannot initialize Missile Manager, unassigned physicChecker!", cgf::Logger::ERROR );
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
		if ( !MissileManager::correctInitialization )
			return;

		MissileManager::missiles.push_back( std::move( missile ) );
		MissileManager::physicChecker->AddBoxCollider( MissileManager::missiles.back() );
	}

	void MissileManager::Update( seconds_t dt )
	{
		if ( !MissileManager::correctInitialization )
			return;

		MissileManager::removeUnusedMissiles();

		for ( auto ptr : missiles )
			ptr->Update( dt );
	}

	void MissileManager::Draw( sf::RenderTarget& target )
	{
		if ( !MissileManager::correctInitialization )
			return;

		for ( auto ptr : missiles )
			ptr->Draw( target );
	}

	void MissileManager::removeUnusedMissiles()
	{
		for ( auto it = MissileManager::missiles.begin(); it != MissileManager::missiles.end();)
		{
			if ( ( *it )->IsWishingDelete() )
				it = MissileManager::missiles.erase( it );
			else
				it++;
		}
	}
}