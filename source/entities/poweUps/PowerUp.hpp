/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

// for seconds_t
#include <framework/Config.hpp>

namespace kd
{
	class Player;

	/*
	===============================================================================
		Special class for Player - modifies its attributes, so it make him immortal
		or something like that. Note:
		Update and Draw methods are called AFTER Player's.

	===============================================================================
	*/
	class PowerUp
	{
	public:
		PowerUp( Player* pPtr ) :
			playerPtr( pPtr )
		{}
		virtual ~PowerUp() = default;

		virtual void Update( seconds_t dt ) {}
		virtual void Draw( sf::RenderTarget& target ) {}

	protected:
		Player* playerPtr;
	};
}
