/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "entities/Player.hpp"

namespace kd
{
	//(it's actually god mode)
	class ImmortalityPowerUp final :
		public PowerUp
	{
	public:
		ImmortalityPowerUp( Player* pPtr ) :
			PowerUp( pPtr ),
			effectTime( SETTINGS.GAMEPLAY.IMMORTAL_EFFECT_TIME )
		{
			this->glowingRect.setFillColor( { sf::Color::Magenta.r, sf::Color::Magenta.g, sf::Color::Magenta.b, 100 } );
			this->glowingRect.setSize( { pPtr->rectangle.width, pPtr->rectangle.height } );
		}

		powerUpID_t GetID() override
		{
			return powerUpID_t::IMMORTAL;
		}

		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target ) override;

	private:
		sf::RectangleShape glowingRect;
		seconds_t effectTime;
	};
}
