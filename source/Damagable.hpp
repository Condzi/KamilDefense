/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "GameConfig.hpp"

namespace kd
{
	class Damagable
	{
	public:
		Damagable() :
			health( 0 ),
			armor( 0 ),
			damageBlockTime( DAMAGE_BLOCK_TIME ),
			pendingDamage( 0 )
		{}

		uint8_t GetHealth() { return this->health; }
		uint8_t GetArmor() { return this->armor; }

		void SetHealth( uint8_t val, bool ignoreLimit = false );
		void SetArmor( uint8_t val, bool ignoreLimit = false );

		void AddDamage( uint8_t val );

	protected:
		uint8_t health;
		uint8_t armor;

		void updateDamage( seconds_t dt );

	private:
		uint8_t pendingDamage;
		seconds_t damageBlockTime;

		void addPendingDamage();
	};
}
