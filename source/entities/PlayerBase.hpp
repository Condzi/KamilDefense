/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "BoxCollider.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"

#include <framework/Logger.hpp>

namespace kd
{
	class Player;

	class PlayerBase final :
		public BoxCollider,
		public Drawable,
		public Entity
	{
	public:
		PlayerBase() :
			BoxCollider( this )
		{}


		void SetPlayerPtr( std::weak_ptr<Player> plPtr );
		void SetPosition( const sf::Vector2f& pos ) override;
		void SetTexture( std::weak_ptr<sf::Texture> t ) override
		{
			cgf::Logger::Log( "You called " + std::string( SHOW_REAL_NAME( *this ) ) + "::SetTexture method - you shouldn't, it doesn't have texture", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
		}

		std::weak_ptr<Player> GetPlayerPtr()
		{
			return this->playerPtr;
		}

		void Draw( sf::RenderTarget& target ) override;

	private:
		std::weak_ptr<Player> playerPtr;
	};
}