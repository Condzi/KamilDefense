/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Settings.hpp"
#include "Types.hpp"

namespace kd
{
	class Entity
	{
	public:
		Entity() :
			position( 0, 0 ),
			wishDelete( false ),
			type( entityID_t::UNINITIALIZED )
		{}
		virtual ~Entity() = default;

		virtual sf::Vector2f GetPosition() { return this->position; }
		virtual bool IsWishingDelete() { return this->wishDelete; }
		virtual entityID_t GetType() { return this->type; }

		virtual void SetPosition( const sf::Vector2f& pos ) { this->position = pos; }
		virtual void SetWishDelete( bool val ) { this->wishDelete = val; }
		virtual void SetType( entityID_t t ) { this->type = t; }

		virtual void Update( seconds_t dt ) {};

	protected:
		sf::Vector2f position;
		bool wishDelete;

	private:
		entityID_t type;
	};
}