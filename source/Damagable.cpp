/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Damagable.hpp"

namespace kd
{
	void Damagable::SetHealth( uint8_t val, bool ignoreLimit )
	{
		if ( val > MAX_HEALTH && !ignoreLimit )
			this->health = MAX_HEALTH;
		else
			this->health = val;
	}

	void Damagable::SetArmor( uint8_t val, bool ignoreLimit )
	{
		if ( val > MAX_ARMOR && !ignoreLimit )
			this->armor = MAX_ARMOR;
		else
			this->armor = val;
	}

	void Damagable::AddDamage( uint8_t val )
	{
		if ( this->damageBlockTime == 0 )
		{
			this->pendingDamage = val;
			this->damageBlockTime = DAMAGE_BLOCK_TIME;
		}
	}

	void Damagable::updateDamage( seconds_t dt )
	{
		if ( this->damageBlockTime > 0.0f )
			this->damageBlockTime -= dt;
		if ( this->damageBlockTime <= 0.0f )
			this->damageBlockTime = 0.0f;

		this->addPendingDamage();
	}

	void Damagable::addPendingDamage()
	{
		if ( this->pendingDamage > this->armor )
			this->pendingDamage -= this->armor;
		else
		{
			this->armor -= this->pendingDamage;
			this->pendingDamage = 0;
		}

		if ( this->pendingDamage )
		{
			if ( this->pendingDamage > this->health )
				this->health = 0;
			else
				this->health -= this->pendingDamage;
		}

		this->pendingDamage = 0;
	}
}