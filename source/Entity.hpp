/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "GameConfig.hpp"
#include "Types.hpp"

namespace kd
{
	class Entity
	{
	public:
		Entity() :
			position( 0, 0 ),
			wishDelete( false ),
			type(UNINITIALIZED)
		{}
		virtual ~Entity() = default;

		entityID_t GetType() { return this->type; }
		sf::Vector2f GetPosition() { return this->position; }
		bool IsWishingDelete() { return this->wishDelete; }

		void SetType( entityID_t t ) { this->type = t; }
		virtual void SetPosition( const sf::Vector2f& pos ) { this->position = pos; }
		void SetWishDelete( bool val ) { this->wishDelete = val; }

		virtual void Update( seconds_t dt ) {};
		virtual void Draw( sf::RenderTarget& target ) {};

	protected:
		sf::Vector2f position;
		bool wishDelete;

	private:
		entityID_t type;
	};
}