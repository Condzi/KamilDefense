/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Player.hpp"

namespace kd
{
	void Player::CheckEvents()
	{
		this->velocity.x = 0.0f;

		if ( sf::Keyboard::isKeyPressed( this->movementKeys.left ) )
			this->velocity.x = this->movementForces.left;

		if ( sf::Keyboard::isKeyPressed( this->movementKeys.right ) )
			this->velocity.x = this->movementForces.right;

		if ( sf::Keyboard::isKeyPressed( this->movementKeys.jump ) &&
			this->grounded )
			this->velocity.y = movementForces.jump;
	}

	void Player::SetPosition( const sf::Vector2f& pos )
	{
		this->position = pos;
		this->rectangle.left = pos.x;
		this->rectangle.top = pos.y;
	}

	void Player::SetTexture( std::shared_ptr<sf::Texture> tex )
	{
		if ( !tex )
			cgf::Logger::log( "Player texture is not assigned", cgf::Logger::WARNING );
		else
		{
			this->texture = tex;

			this->sprite.setTexture( *this->texture );
			this->sprite.setScale( SCALE, SCALE );

			this->rectangle = this->sprite.getGlobalBounds();
		}
	}

	void Player::SetHealth( uint8_t val, bool ignoreLimit )
	{
		if ( val > MAX_HEALTH && !ignoreLimit )
			this->health = MAX_HEALTH;
		else
			this->health = val;
	}

	void Player::SetArmor( uint8_t val, bool ignoreLimit )
	{
		if ( val > MAX_ARMOR && !ignoreLimit )
			this->armor = MAX_ARMOR;
		else
			this->armor = val;
	}

	void Player::AddDamage( uint8_t val )
	{
		if ( val > this->armor )
			val = val - this->armor;
		else
			this->armor -= val;

		if ( val )
		{
			if ( val > this->health )
				this->health = 0;
			else
				this->health -= val;
		}
	}

	void Player::Update( seconds_t dt )
	{
		if ( velocity.y != 0.0f )
			this->grounded = false;

		this->velocity.y += GRAVITY * OBJECT_WEIGHT * dt;

		this->rectangle.left += velocity.x * dt;
		this->rectangle.top += velocity.y * dt;

		this->position = { this->rectangle.left, this->rectangle.top };

		this->sprite.setPosition( this->position );
	}

	void Player::Draw( sf::RenderTarget& target )
	{
		if ( !this->texture )
			cgf::Logger::log( "Player texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		else
			target.draw( this->sprite );
	}
}