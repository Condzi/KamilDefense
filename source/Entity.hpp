/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include "Types.hpp"

namespace kd
{
	class Entity 
	{
	public:
		Entity() :
			position(0,0)
		{}
		virtual ~Entity() = default;

		sf::Vector2f getPosition() { return position; }

		void setPosition(const sf::Vector2f& pos) { position = pos;	}

		virtual void update(seconds_t dt) {};
		virtual void draw(sf::RenderTarget& target) {};
	
	private:
		int16_t type;

	protected:
		sf::Vector2f position;
	};
}