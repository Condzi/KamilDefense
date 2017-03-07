/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "GameConfig.hpp"
#include "Types.hpp"

namespace kd
{
	class Damagable
	{
	public:
		Damagable() :
			health( 0 ),
			armor( 0 ),
			lifeState( lifeState_t::Alive ),
			damageBlockTime( DAMAGE_BLOCK_TIME ),
			pendingDamage( 0 )
		{}

		uint8_t GetHealth() { return this->health; }
		uint8_t GetArmor() { return this->armor; }
		lifeState_t GetLifeState() { return this->lifeState; }

		void SetHealth( uint8_t val, bool ignoreLimit = false );
		void SetArmor( uint8_t val, bool ignoreLimit = false );

		void AddDamage( uint8_t val );

	protected:
		uint8_t health;
		uint8_t armor;
		lifeState_t lifeState;

		void updateDamage( seconds_t dt );

	private:
		uint8_t pendingDamage;
		seconds_t damageBlockTime;

		void updateLifeState();
		void addPendingDamage();
	};
}
