/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Immortality.hpp"

namespace kd
{
	void ImmortalityPowerUp::Update( seconds_t dt )
	{
		this->playerPtr->SetHealth( kd::settings_t::GetInstance().GAMEPLAY.MAX_HEALTH );
		this->playerPtr->SetArmor( kd::settings_t::GetInstance().GAMEPLAY.MAX_ARMOR );
		this->glowingRect.setPosition( this->playerPtr->GetPosition() );

		this->glowingRect.setFillColor( { uint8_t( this->glowingRect.getFillColor().r + 10 ),
										uint8_t( this->glowingRect.getFillColor().g + 5 ),
										this->glowingRect.getFillColor().b,
										100 } );
		this->effectTime -= dt;

		if ( this->effectTime <= 0 )
			this->removeFromPlayer = true;
	}

	void ImmortalityPowerUp::Draw( sf::RenderTarget& target )
	{
		target.draw( this->glowingRect );
	}
}