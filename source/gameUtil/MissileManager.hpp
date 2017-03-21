/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <framework/Logger.hpp>

#include "CollisionChecker.hpp"
#include "entities/Missile.hpp"

namespace kd
{
	class MissileManager final
	{
	public:
		MissileManager() = delete;

		static void Initialize( CollisionChecker* physicCh, std::vector<std::shared_ptr<Entity>>* entPtr );
		static void Shutdown();

		static void AddMissile( std::shared_ptr<Missile> missile );

		static void Update( seconds_t dt );

	private:
		static bool initialized;
		static std::vector<std::weak_ptr<Missile>> missiles;
		static CollisionChecker* collisionCheckerPtr;
		static std::vector<std::shared_ptr<Entity>>* entitiesPtr;

		static void removeUnusedMissiles();
		static bool isInWindowBounds( const sf::Vector2f& pos );
	};
}