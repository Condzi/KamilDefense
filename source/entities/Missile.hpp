/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <framework/Logger.hpp>

#include "BoxCollider.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"

namespace kd
{
	class MissileManager;

	class Missile final :
		public BoxCollider,
		public Drawable,
		public Entity
	{
		friend class CollisionSolver;

	public:
		Missile();

		void SetType( entityID_t type ) override;
		void SetTexture( std::weak_ptr<sf::Texture> tex ) override
		{
			cgf::Logger::Log( "You called " + std::string( SHOW_REAL_NAME( *this ) ) + "::SetTexture method - you shouldn't, it doesn't have texture", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		}
		void SetPosition( const sf::Vector2f& pos ) override;

		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target ) override;

	private:
		sf::RectangleShape shape;
		float weight;
	};
}
