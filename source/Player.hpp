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
	class Player final : public Entity, public BoxCollider
	{
	public:
		Player() :
			BoxCollider( this ),
			health( 0 ),
			armor( 0 ),
			movementKeys( sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up ),
			movementForces( -25.f, 25.f, 50.f )
		{}

		uint8_t GetHealth() { return this->health; }
		uint8_t GetArmor() { return this->armor; }

		void SetPosition( const sf::Vector2f& pos ) override;
		void SetTexture( std::shared_ptr<sf::Texture> texture );
		void SetHealth( uint8_t val, bool ignoreLimit = false );
		void SetArmor( uint8_t val, bool ignoreLimit = false );
		void SetMovementKeys( const movementKeys_t& keys ) { this->movementKeys = keys; }
		void SetMovementForces( const movementForces_t& forces ) { this->movementForces = forces; }

		void AddDamage( uint8_t val );

		void Update( seconds_t dt ) override;
		void CheckEvents();
		void Draw( sf::RenderTarget& target ) override;

	private:
		uint8_t health;
		uint8_t armor;

		movementKeys_t movementKeys;
		movementForces_t movementForces;

		std::shared_ptr<sf::Texture> texture;
		sf::Sprite sprite;
	};
}
