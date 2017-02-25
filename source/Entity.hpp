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
			position(0,0),
			wishDelete(false)
		{}
		virtual ~Entity() = default;

		ENTITY_ID getType() { return type; }
		sf::Vector2f getPosition() { return position; }
		bool isWishingDelete() { return wishDelete; }

		void setType(ENTITY_ID t) { type = t; }
		virtual void setPosition(const sf::Vector2f& pos) { position = pos;	}
		void setWishDelete(bool val) { wishDelete = val; }

		virtual void update(seconds_t dt) {};
		virtual void draw(sf::RenderTarget& target) {};
	
	private:
		ENTITY_ID type;

	protected:
		sf::Vector2f position;
		bool wishDelete;
	};
}