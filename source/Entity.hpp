/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Types.hpp"

namespace kd
{
	// Representation of Entity data - to get it from entity use Entity::get()->... 
	class EntityResource final
	{
	public:
		EntityResource() :
			position(0,0)
		{}

		virtual void update(seconds_t dt) = 0;

		sf::Vector2f getPosition() { return position; }
		
		void setPosition(const sf::Vector2f& pos) { position = pos; }

	protected:
		sf::Vector2f position;
	};	

	// Type declared only for inheritance
	struct Entity : public cgf::Resource<EntityResource>
	{};
}