/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Player.hpp"

namespace kd
{
	void Player::checkEvents()
	{
		if (sf::Keyboard::isKeyPressed(movementKeys.left))
			velocity.x = movementForces.left;

		if (sf::Keyboard::isKeyPressed(movementKeys.right))
			velocity.x = movementForces.right;

		if (sf::Keyboard::isKeyPressed(movementKeys.jump) &&
			velocity.y == 0.f)
			velocity.y = movementForces.jump;
	}

	void Player::setTexture(std::shared_ptr<sf::Texture> tex)
	{
		if (!tex)
			cgf::Logger::log("Player texture is not assigned", cgf::Logger::WARNING);
		else
		{
			texture = tex;

			sprite.setTexture(*texture);
			sprite.setScale(SCALE, SCALE);

			rectangle = sprite.getGlobalBounds();
		}
	}

	void Player::setHealth(uint8_t val, bool ignoreLimit)
	{
		if (val > MAX_HEALTH && !ignoreLimit)
			health = MAX_HEALTH;
		else
			health = val;
	}

	void Player::setArmor(uint8_t val, bool ignoreLimit)
	{
		if (val > MAX_ARMOR && !ignoreLimit)
			armor = MAX_ARMOR;
		else
			armor = val;
	}

	void Player::addDamage(uint8_t val)
	{
		if (val > armor)
			val = val - armor;
		else
			armor -= val;

		if (val)
		{
			if (val > health)
				health = 0;
			else
				health -= val;
		}
	}

	void Player::update(seconds_t dt)
	{
		velocity.x = 0;
		velocity.y += GRAVITY * dt;

		checkEvents();

		position += velocity * dt;

		rectangle.left = position.x; 
		rectangle.top = position.y;
		sprite.setPosition(position);
	}

	void Player::draw(sf::RenderTarget& target)
	{
		if (!texture)
			cgf::Logger::log("Player texture is not set, nothing will be drawn", cgf::Logger::WARNING, cgf::Logger::CONSOLE);
		else
			target.draw(sprite);
	}
}