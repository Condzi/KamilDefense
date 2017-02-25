/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Logger.hpp>

#include "BoxCollider.hpp"
#include "Entity.hpp" 
#include "GameConfig.hpp"

namespace kd
{
	class Player final :
		public Entity,
		public BoxCollider
	{
	public:
		Player() :
			BoxCollider(std::make_shared<Entity>(*this)),
			health(0),
			armor(0),
			movementKeys(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up),
			movementForces(-25.f, 25.f, 50.f)
		{}

		uint8_t getHealth() { return health; }
		uint8_t getArmor() { return armor; }

		void setPosition( const sf::Vector2f& pos ) override;
		void setTexture(std::shared_ptr<sf::Texture> texture);
		void setHealth(uint8_t val, bool ignoreLimit = false);
		void setArmor(uint8_t val, bool ignoreLimit = false);
		void setMovementKeys(const movement_keys_t& keys) { movementKeys = keys; }
		void setMovementForces(const movement_forces_t& forces) { movementForces = forces; }

		void addDamage(uint8_t val);

		void update(seconds_t dt) override;
		void checkEvents();
		void draw(sf::RenderTarget& target) override;

	private:
		uint8_t health;
		uint8_t armor;

		movement_keys_t movementKeys;
		movement_forces_t movementForces;

		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite;
	};
}
