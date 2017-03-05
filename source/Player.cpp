/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Player.hpp"

namespace kd
{
	void Player::CheckEvents()
	{
		checkMovementEvents();
		checkShootingEvents();
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
			cgf::Logger::Log( "Player texture is not assigned", cgf::Logger::WARNING );
		else
		{
			this->texture = tex;

			this->sprite.setTexture( *this->texture.lock() );
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
		if ( this->damageBlockTime == 0 )
		{
			this->pendingDamage = val;
			this->damageBlockTime = DAMAGE_BLOCK_TIME;
		}
	}

	void Player::Update( seconds_t dt )
	{
		this->updateMovement( dt );

		if ( this->damageBlockTime > 0 )
			this->damageBlockTime -= dt;
		if ( this->damageBlockTime <= 0 )
			this->damageBlockTime = 0;

		this->addPendingDamage();
	}

	void Player::Draw( sf::RenderTarget& target )
	{
		if ( this->texture.expired() )
			cgf::Logger::Log( "Player texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		else
			target.draw( this->sprite );
	}

	void Player::addPendingDamage()
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

	void Player::checkMovementEvents()
	{
		this->velocity.x = 0.0f;

		if ( sf::Keyboard::isKeyPressed( this->movementKeys.left ) )
			this->velocity.x = this->movementForces.left;

		if ( sf::Keyboard::isKeyPressed( this->movementKeys.right ) )
			this->velocity.x = this->movementForces.right;

		if ( sf::Keyboard::isKeyPressed( this->movementKeys.jump ) &&
			this->grounded )
			this->velocity.y = this->movementForces.jump;
	}

	void Player::checkShootingEvents()
	{
		float bulletVelocityX = 0.0f;
		sf::Vector2f bulletStartPosition = { 0.0f,0.0f };
		bool shoot = false;

		if ( sf::Keyboard::isKeyPressed( this->shootingKeys.left ) )
		{
			bulletVelocityX = -MISSILE_X_VELOCITY;
			shoot = true;
		}

		if ( sf::Keyboard::isKeyPressed( this->shootingKeys.right ) )
		{
			bulletVelocityX = MISSILE_X_VELOCITY;
			shoot = true;
		}

		if ( shoot )
		{
			auto missile = std::make_shared<Missile>();

			// temporary
			bulletStartPosition = this->position;
			missile->SetPosition( bulletStartPosition );
			missile->rectangle.width = 5.0f;
			missile->rectangle.height = 2.5f;
			missile->SetType( entityID_t::BULLET_PLAYER );
			missile->velocity.x = bulletVelocityX;
			MissileManager::AddMissile( missile );
		}
	}

	void Player::updateMovement( seconds_t dt )
	{
		if ( velocity.y != 0.0f )
			this->grounded = false;

		this->velocity.y += GRAVITY * OBJECT_WEIGHT * dt;

		this->rectangle.left += this->velocity.x * dt;
		this->rectangle.top += this->velocity.y * dt;

		this->position = { this->rectangle.left, this->rectangle.top };

		this->sprite.setPosition( this->position );
	}
}