/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Missile.hpp"

namespace kd
{
	Missile::Missile() :
		BoxCollider( this ),
		weight( 0.0f )
	{
		this->shape.setPosition( this->position );
	}

	void Missile::SetType( entityID_t t )
	{
		this->Entity::SetType( t );

		if ( t == entityID_t::BULLET_PLAYER )
		{
			this->shape.setFillColor( sf::Color::Yellow );
			this->weight = SETTINGS.GAMEPLAY.PLAYER_MISSILE_WEIGHT;
		} else
		{
			this->shape.setFillColor( sf::Color::Green );
			this->weight = SETTINGS.GAMEPLAY.ENEMY_MISSILE_WEIGHT;
		}
	}

	void Missile::SetPosition( const sf::Vector2f& pos )
	{
		this->position = pos;
		this->rectangle.left = pos.x;
		this->rectangle.top = pos.y;
		this->shape.setPosition( this->position );
	}

	void Missile::Update( seconds_t dt )
	{
		this->velocity.y += SETTINGS.GAMEPLAY.GRAVITY * this->weight * dt;
		this->shape.setSize( { this->rectangle.width, this->rectangle.height } );

		this->rectangle.left += this->velocity.x * dt;
		this->rectangle.top += this->velocity.y * dt;

		this->position = { this->rectangle.left, this->rectangle.top };
		this->shape.setPosition( this->position );
	}

	void Missile::Draw( sf::RenderTarget& target )
	{
		target.draw( shape );
	}
}