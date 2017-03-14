/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <Logger.hpp>

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

		void SetPosition( const sf::Vector2f& pos ) override;
		void SetTexture( std::weak_ptr<sf::Texture> tex ) override
		{
			cgf::Logger::Log( "You call Missile SetTexture() method - you shouldn't, it doesn't have texture when drawing rectangle", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		}

		void Update( seconds_t dt ) override;
		void Draw( sf::RenderTarget& target ) override;

	private:
		sf::RectangleShape shape;
	};
}
