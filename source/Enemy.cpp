/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Enemy.hpp"

namespace kd
{
	void Enemy::SetHealth( uint8_t val, bool ignoreLimit )
	{
		if ( val > MAX_HEALTH && !ignoreLimit )
			this->health = MAX_HEALTH;
		else
			this->health = val;
	}

	void Enemy::SetTexture( std::shared_ptr<sf::Texture> tex )
	{
		if ( !tex )
			cgf::Logger::Log( "Enemy texture is not assigned", cgf::Logger::WARNING );
		else
		{
			this->texture = tex;

			this->sprite.setTexture( *this->texture.lock() );
			this->sprite.setScale( SCALE, SCALE );

			this->rectangle = this->sprite.getGlobalBounds();
		}
	}

	void Enemy::SetPosition( const sf::Vector2f& pos )
	{
		this->position = pos;
		this->rectangle.left = pos.x;
		this->rectangle.top = pos.y;
	}

	void Enemy::AddDamage( uint8_t val )
	{
		if ( this->damageBlockTime == 0 )
		{
			this->pendingDamage = val;
			this->damageBlockTime = DAMAGE_BLOCK_TIME;
		}
	}

	void Enemy::Update( seconds_t dt )
	{
		this->velocity.y += GRAVITY * OBJECT_WEIGHT * dt;

		this->rectangle.left += velocity.x * dt;
		this->rectangle.top += velocity.y * dt;

		this->position = { this->rectangle.left, this->rectangle.top };

		this->sprite.setPosition( this->position );

		if ( this->damageBlockTime > 0 )
			this->damageBlockTime -= dt;
		if ( this->damageBlockTime <= 0 )
			this->damageBlockTime = 0;

		addPendingDamage();
	}
	void Enemy::Draw( sf::RenderTarget& target )
	{
		if ( this->texture.expired() )
			cgf::Logger::Log( "Enemy texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		else
			target.draw( this->sprite );
	}

	void Enemy::addPendingDamage()
	{
		if ( this->pendingDamage )
		{
			if ( this->pendingDamage > this->health )
				this->wishDelete = true;
			else
				this->health -= this->pendingDamage;
		}
		this->pendingDamage = 0;
	}
}