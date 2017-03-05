/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Missile.hpp"

namespace kd
{
	Missile::Missile() :
		BoxCollider( this )
	{
		this->shape.setPosition( this->position );
	}

	void Missile::SetPosition( const sf::Vector2f & pos )
	{
		this->position = pos;
		this->rectangle.left = pos.x;
		this->rectangle.top = pos.y;
		this->shape.setPosition( this->position );
	}

	void Missile::Update( seconds_t dt )
	{
		if ( this->shape.getFillColor() == sf::Color::White )
		{
			if ( this->GetType() == entityID_t::BULLET_PLAYER )
				this->shape.setFillColor( sf::Color::Yellow );
			else
				this->shape.setFillColor( sf::Color::Blue );
		}

		this->velocity.y += GRAVITY * ( OBJECT_WEIGHT / 5.0f ) * dt;
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