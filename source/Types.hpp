/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <Config.hpp>

namespace kd
{
	enum collisionSide_t
	{
		None = -1,
		Left = 0,
		Right,
		Down,
		Top
	};

	enum lifeState_t
	{
		Alive = 0,
		Dying,
		Dead
	};

	struct shootingKeys_t final
	{
		sf::Keyboard::Key left, right;

		shootingKeys_t( sf::Keyboard::Key l, sf::Keyboard::Key r ) :
			left( l ), right( r )
		{}
	};

	struct movementKeys_t final
	{
		sf::Keyboard::Key left, right, jump;

		movementKeys_t( sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j ) :
			left( l ), right( r ), jump( j )
		{}
	};

	struct movementForces_t final
	{
		float left, right, jump;

		movementForces_t( float l, float r, float j ) :
			left( l ), right( r ), jump( j )
		{}
	};
}
