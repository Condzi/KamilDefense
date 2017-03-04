/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Logger.hpp>

#include "PhysicsChecker.hpp"
#include "Missile.hpp"

namespace kd
{
	class MissileManager final
	{
	public:
		MissileManager() = delete;

		static void Initialize( std::shared_ptr<PhysicsChecker> physicCh );
		static void Shutdown();

		static void AddMissile( std::shared_ptr<Missile> missile );

		static void Update( seconds_t dt );
		static void Draw( sf::RenderTarget& target );

	private:
		static bool correctInitialization;
		static std::vector<std::shared_ptr<Missile>> missiles;
		static std::weak_ptr<PhysicsChecker> physicChecker;

		static void removeUnusedMissiles();
	};
}