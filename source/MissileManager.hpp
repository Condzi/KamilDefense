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

		static void Initialize( PhysicsChecker* physicCh );
		static void Shutdown();

		static void AddMissile( std::shared_ptr<Missile> missile );

		static void Update( seconds_t dt );
		static void Draw( sf::RenderTarget& target );

	private:
		static bool initielized;
		static std::vector<std::shared_ptr<Missile>> missiles;
		static PhysicsChecker* physicChecker;

		static void removeUnusedMissiles();
		static bool isInWindowBounds( const sf::Vector2f& pos );
	};
}