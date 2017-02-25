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
	enum collision_side_t 
	{
		None = -1,
		Left = 0,
		Right,
		Down,
		Top
	};

	struct movement_keys_t final
	{
		sf::Keyboard::Key left, right, jump;

		movement_keys_t(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j) :
			left(l), right(r), jump(j)
		{}
	};

	struct movement_forces_t final
	{
		float left, right, jump;

		movement_forces_t(float l, float r, float j) :
			left(l), right(r), jump(j)
		{}
	};
}
