/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>
#include <memory>

#include <Resource.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

namespace kd
{
	class EntityResource;

	using seconds_t = float;
	using EntityPtr = std::shared_ptr<EntityResource>;

	enum collision_side_t 
	{
		None = -1,
		Left = 0,
		Right,
		Top,
		Down
	};

	struct movement_keys_t final
	{
		sf::Keyboard::Key left, right, jump;
	};

	struct movement_forces_t final
	{
		float left, right, jump;
	};

}
