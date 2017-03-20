/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PlayerBase.hpp"

namespace kd
{
	void PlayerBase::SetPlayerPtr( std::weak_ptr<Player> plPtr )
	{
		if ( plPtr.expired() )
			cgf::Logger::Log( "Player pointer in PlayerBase is not assigned / is expired", cgf::Logger::ERROR );
		else
			this->playerPtr = plPtr;
	}

	void PlayerBase::SetPosition( const sf::Vector2f& pos )
	{
		this->position = pos;
		this->rectangle.left = this->position.x;
		this->rectangle.top = this->position.y;
	}

	void PlayerBase::Draw( sf::RenderTarget& target )
	{
		if ( !DEBUG_DRAW_BORDERS )
			return;

		sf::RectangleShape shape;
		shape.setPosition( this->rectangle.left, this->rectangle.top );
		shape.setSize( { this->rectangle.width,this->rectangle.height } );
		shape.setFillColor( sf::Color::Transparent );
		shape.setOutlineThickness( 2.0f );
		shape.setOutlineColor( sf::Color::Yellow );

		target.draw( shape );
	}
}