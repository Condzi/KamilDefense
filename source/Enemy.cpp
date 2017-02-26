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
			cgf::Logger::log( "Enemy texture is not assigned", cgf::Logger::WARNING );
		else
		{
			this->texture = tex;

			this->sprite.setTexture( *this->texture );
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
		if ( val )
		{
			if ( val > this->health )
				this->wishDelete = true;
			else
				this->health -= val;
		}
	}

	void Enemy::Update( seconds_t dt )
	{
		this->velocity.y += GRAVITY * OBJECT_WEIGHT * dt;

		this->rectangle.left += velocity.x * dt;
		this->rectangle.top += velocity.y * dt;

		this->position = { this->rectangle.left, this->rectangle.top };

		this->sprite.setPosition( this->position );
	}
	void Enemy::Draw( sf::RenderTarget& target )
	{
		if ( !this->texture )
			cgf::Logger::log( "Enemy texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		else
			target.draw( this->sprite );
	}
}