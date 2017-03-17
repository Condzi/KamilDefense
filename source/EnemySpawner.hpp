/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include "Enemy.hpp"
#include "CollisionChecker.hpp"

namespace kd
{
	class EnemySpawner :
		public Entity
	{
	public:
		EnemySpawner() :
			physicCheckerPtr( nullptr ),
			entitiesVectorPtr( nullptr ),
			startVelocity( 0, 0 ),
			spawningTimeEleapsed( 0 ),
			spawningTime( 0 )
		{}

		void SetPhysicChecker( CollisionChecker* phChPtr );
		void SetEntitiesVector( std::vector<std::shared_ptr<Entity>>* enVecPtr );
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
		std::vector<std::shared_ptr<Entity>>* entitiesVectorPtr;
		std::weak_ptr<sf::Texture> enemyTexture;

		sf::Vector2f startVelocity;
		seconds_t spawningTimeEleapsed;
		seconds_t spawningTime;

		void spawnEnemy();
	};
}