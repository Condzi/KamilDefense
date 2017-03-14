/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include <Logger.hpp>

#include "BoxCollider.hpp"
#include "Damagable.hpp"
#include "Drawable.hpp"
#include "Entity.hpp" 
#include "GameConfig.hpp"
#include "MissileManager.hpp"

namespace kd
{
	class Player final :
		public BoxCollider,
		public Drawable,
		public Entity,
		public Damagable
	{
	public:
		Player() :
			BoxCollider( this ),
			shootingKeys( sf::Keyboard::Left, sf::Keyboard::Right ),
			movementKeys( sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space ),
			movementForces( -25.0f, 25.0f, 50.0f )
		{}

		void SetPosition( const sf::Vector2f& pos ) override;
		void SetTexture( std::weak_ptr<sf::Texture> texture ) override;
		void SetMovementKeys( const movementKeys_t& keys )
		{
			this->movementKeys = keys;
		}
		void SetMovementForces( const movementForces_t& forces )
		{
			this->movementForces = forces;
		}

		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target ) override;

	private:
		shootingKeys_t shootingKeys;
		movementKeys_t movementKeys;
		movementForces_t movementForces;

		sf::Sprite sprite;

		void checkMovementEvents();
		void checkShootingEvents();
		void checkEvents();

		void updateMovement( seconds_t dt );
	};
}
