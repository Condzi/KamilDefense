/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Player.hpp"

namespace kd
{
	void Player::SetPosition( const sf::Vector2f& pos )
	{
		this->position = pos;
		this->rectangle.left = pos.x;
		this->rectangle.top = pos.y;
	}

	void Player::SetTexture( std::weak_ptr<sf::Texture> tex )
	{
		this->setTextureSheet( tex );

		this->sprite.setScale( kd::settings_t::GetInstance().GAMEPLAY.SCALE, kd::settings_t::GetInstance().GAMEPLAY.SCALE );
	}

	void Player::UpdateCollider()
	{
		this->rectangle.width = this->GetFrame( 0 ).width * kd::settings_t::GetInstance().GAMEPLAY.SCALE;
		this->rectangle.height = this->GetFrame( 0 ).height * kd::settings_t::GetInstance().GAMEPLAY.SCALE;
	}

	void Player::Update( seconds_t dt )
	{
		this->updateMovement( dt );
		this->checkEvents();
		this->updateDamage( dt );
		this->updatePowerUps( dt );
		this->animationUpdate( dt );
	}

	void Player::Draw( sf::RenderTarget& target )
	{
		if ( this->sprite.getTexture() == nullptr )
			cgf::Logger::Log( "Player texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		else
			target.draw( this->sprite );

		this->drawPowerUps( target );
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
		float posXoffset = 0.0f;
		bool shoot = false;

		if ( sf::Keyboard::isKeyPressed( this->shootingKeys.left ) )
		{
			bulletVelocityX = -kd::settings_t::GetInstance().GAMEPLAY.PLAYER_MISSILE_SPEED_X;
			shoot = true;
		}

		if ( sf::Keyboard::isKeyPressed( this->shootingKeys.right ) )
		{
			bulletVelocityX = kd::settings_t::GetInstance().GAMEPLAY.PLAYER_MISSILE_SPEED_X;
			posXoffset = -1.5f * kd::settings_t::GetInstance().GAMEPLAY.SCALE;
			shoot = true;
		}

		if ( shoot )
		{
			auto missile = std::make_shared<Missile>();

			missile->SetPosition( { this->position.x + ( 3 * kd::settings_t::GetInstance().GAMEPLAY.SCALE ) + posXoffset, this->position.y + ( 5 * kd::settings_t::GetInstance().GAMEPLAY.SCALE ) } );
			missile->rectangle.width = 5.0f;
			missile->rectangle.height = 2.5f;
			missile->SetType( entityID_t::BULLET_PLAYER );
			missile->velocity.x = bulletVelocityX;
			missile->velocity.y = kd::settings_t::GetInstance().GAMEPLAY.PLAYER_MISSILE_START_SPEED_Y;
			MissileManager::AddMissile( missile );
		}
	}

	void Player::updateMovement( seconds_t dt )
	{
		if ( this->velocity.y != 0.0f )
			this->grounded = false;

		this->velocity.y += kd::settings_t::GetInstance().GAMEPLAY.GRAVITY * kd::settings_t::GetInstance().GAMEPLAY.DEFAULT_OBJECT_WEIGHT * dt;

		this->rectangle.left += this->velocity.x * dt;
		this->rectangle.top += this->velocity.y * dt;

		this->position = { this->rectangle.left, this->rectangle.top };

		this->sprite.setPosition( this->position );
	}

	void Player::updatePowerUps( seconds_t dt )
	{
		for ( auto it = this->powerUps.begin(); it != this->powerUps.end();)
		{
			if ( ( *it )->GetRemoveFromPlayer() )
				it = this->powerUps.erase( it );
			else
				it++;
		}

		for ( auto& ptr : this->powerUps )
			ptr->Update( dt );
	}

	void Player::drawPowerUps( sf::RenderTarget & target )
	{
		for ( auto& ptr : this->powerUps )
			ptr->Draw( target );
	}

	void Player::checkEvents()
	{
		this->checkMovementEvents();
		this->checkShootingEvents();
	}
}