/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "EnemySpawner.hpp"

namespace kd
{
	void EnemySpawner::SetPhysicChecker( CollisionChecker * phChPtr )
	{
		if ( !phChPtr )
			cgf::Logger::Log( "PhysicChecker pointer is not assinged in EnemySpawner", cgf::Logger::WARNING );

		this->physicCheckerPtr = phChPtr;
	}

	void EnemySpawner::SetEntityManager( EntityManager* entityMgr )
	{
		if ( !entityMgr )
			cgf::Logger::Log( "Entity Manager pointer is not assigned in EnemySpawner", cgf::Logger::WARNING );

		this->entityManagerPtr = entityMgr;
	}

	void EnemySpawner::SetEnemyTexture( std::weak_ptr<sf::Texture> tex )
	{
		if ( tex.expired() )
			cgf::Logger::Log( "Texture pointer is not assigned in EnemySpawner", cgf::Logger::WARNING );

		this->enemyTexture = tex;
	}

	void EnemySpawner::Update( seconds_t dt )
	{
		this->spawningTimeEleapsed -= dt;

		if ( this->spawningTimeEleapsed <= 0.0f )
		{
			this->spawningTimeEleapsed = this->spawningTime;
			this->spawnEnemy();
		}
	}

	void EnemySpawner::spawnEnemy()
	{
		auto enemy = std::make_shared<Enemy>();

		enemy->SetType( entityID_t::ENEMY );
		enemy->SetDrawLayer( 1 );
		enemy->SetPosition( this->position );
		enemy->SetHealth( 100 );
		enemy->velocity = this->startVelocity;
		enemy->SetTexture( this->enemyTexture.lock() );

		//cgf::Logger::Log( "Spawned Enemy at: X( " + std::to_string( this->position.x ) + " ) Y( " + std::to_string( this->position.y ) + " )" );

		this->entityManagerPtr->AddEntity( enemy );
		this->physicCheckerPtr->AddBoxCollider( enemy );
	}
}