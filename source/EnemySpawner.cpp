/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "EnemySpawner.hpp"

namespace kd
{
	void EnemySpawner::SetPhysicChecker( PhysicsChecker * phChPtr )
	{
		if ( !phChPtr )
			cgf::Logger::Log( "PhysicChecker pointer is not assinged in EnemySpawner", cgf::Logger::WARNING );

		this->physicCheckerPtr = phChPtr;
	}

	void EnemySpawner::SetEntitiesVector( std::vector<std::shared_ptr<Entity>>* enVecPtr )
	{
		if ( !enVecPtr )
			cgf::Logger::Log( "Entity Vector pointer is not assigned in EnemySpawner", cgf::Logger::WARNING );

		this->entitiesVectorPtr = enVecPtr;
	}

	void EnemySpawner::SetEnemyTexture( std::shared_ptr<sf::Texture> tex )
	{
		if ( !tex )
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
		enemy->SetPosition( this->position );
		enemy->SetHealth( 100 );
		enemy->velocity = this->startVelocity;
		enemy->SetTexture( this->enemyTexture.lock() );

		this->entitiesVectorPtr->push_back( enemy );
		this->physicCheckerPtr->AddBoxCollider( std::dynamic_pointer_cast<Enemy>( this->entitiesVectorPtr->back() ) );
	}
}