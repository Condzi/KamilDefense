/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include "Enemy.hpp"
#include "gameUtil/CollisionChecker.hpp"
#include "entities/EntityManager.hpp"

namespace kd
{
	class EnemySpawner :
		public Entity
	{
	public:
		EnemySpawner() :
			physicCheckerPtr( nullptr ),
			entityManagerPtr( nullptr ),
			startVelocity( 0, 0 ),
			spawningTimeEleapsed( 0 ), spawningTime( 0 )
		{}

		void SetPhysicChecker( CollisionChecker* phChPtr );
		void SetEntityManager( EntityManager* entityMgr );
		void SetEnemyTexture( std::weak_ptr<sf::Texture> tex );
		void SetStartVelocity( const sf::Vector2f& vel )
		{
			this->startVelocity = vel;
		}
		void SetSpawningTime( seconds_t time )
		{
			this->spawningTime = time;
		}

		void Update( seconds_t dt ) override;

	private:
		CollisionChecker* physicCheckerPtr;
		EntityManager* entityManagerPtr;
		std::weak_ptr<sf::Texture> enemyTexture;

		sf::Vector2f startVelocity;
		seconds_t spawningTimeEleapsed, spawningTime;

		void spawnEnemy();
	};
}