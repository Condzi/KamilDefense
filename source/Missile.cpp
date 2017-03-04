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
		this->shape.setSize( { this->rectangle.width, this->rectangle.height } );
		this->shape.setFillColor( sf::Color::Transparent );
		this->shape.setOutlineThickness( 0.5f );
		this->shape.setPosition( this->position );

		if ( this->GetType() == entityID_t::PLAYER )
			shape.setOutlineColor( sf::Color::Yellow );
		else
			shape.setOutlineColor( sf::Color::Blue );
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
		this->velocity.y += GRAVITY * ( OBJECT_WEIGHT / 10.0f ) * dt;

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