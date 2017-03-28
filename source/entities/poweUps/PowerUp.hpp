/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

// for seconds_t
#include <framework/Config.hpp>

#include "Types.hpp"

namespace kd
{
	class Player;

	/*
	===============================================================================
		Special class for Player - modifies its attributes, so it make him immortal
		or something like that. Note:
		Update and Draw methods are called AFTER Players.

	===============================================================================
	*/
	class PowerUp
	{
	public:
		PowerUp( Player* pPtr ) :
			playerPtr( pPtr ),
			removeFromPlayer( false )
		{}
		virtual ~PowerUp() = default;

		virtual powerUpID_t GetID() 
		{ 
			return powerUpID_t::UNITIALIZED; 
		}
		bool GetRemoveFromPlayer()
		{
			return this->removeFromPlayer;
		}

		virtual void Update( seconds_t dt ) {}
		virtual void Draw( sf::RenderTarget& target ) {}

	protected:
		Player* playerPtr;
		bool removeFromPlayer;
	};
}
