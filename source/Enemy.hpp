/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Logger.hpp>

#include "BoxCollider.hpp"
#include "Entity.hpp"
#include "MissileManager.hpp"

namespace kd
{
	class Enemy :
		public Entity,
		public BoxCollider
	{
	public:
		Enemy() :
			BoxCollider( this ),
			health( 0 ),
			pendingDamage( 0 ),
			damageBlockTime( DAMAGE_BLOCK_TIME ),
			shootTime( ENEMY_SHOOT_COOLDOWN )
		{
			// temporary
			this->velocity = { 250.f, 0.0f };
		}

		uint8_t GetHealth() { return this->health; }

		void SetHealth( uint8_t val, bool ignoreLimit = false );
		void SetTexture( std::shared_ptr<sf::Texture> tex );
		void SetPosition( const sf::Vector2f& pos ) override;

		void AddDamage( uint8_t val );

		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target );

	private:
		std::weak_ptr<sf::Texture> texture;
		sf::Sprite sprite;

		uint8_t health;
		uint8_t pendingDamage;
		seconds_t damageBlockTime;

		seconds_t shootTime;

	private:
		void addPendingDamage();
		void updateMovement( seconds_t dt );
		void shoot();
	};
}
