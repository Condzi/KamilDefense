/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <framework/Config.hpp>

#include "ResourceWrapper.hpp"


namespace kd
{
	using textureResource_t = ResourceWrapper<sf::Texture>;
	using fontResource_t = ResourceWrapper<sf::Font>;
	using textResource_t = ResourceWrapper<sf::Text>;

	enum class resourcePriorites_t
	{
		UI_GAME = 0,
		UI_MENU,
		ENTITIES,
		LEVEL
	};

	enum class textureResourceID_t
	{
		LEVEL_BG = 0,
		MENU_BG,
		ENEMY,
		PLAYER,

		count
	};

	enum class uiTextResourceID_t
	{
		HP_1 = static_cast<uint8_t>( textureResourceID_t::count ),
		HP_2,
		HP_3,
		ARMOR,
		BASE_HP,

		count
	};

	enum class fontResourceID_t
	{
		UI_FONT = static_cast<uint8_t>( uiTextResourceID_t::count ),

		count
	};

	enum class collisionSide_t
	{
		NONE = -1,
		LEFT = 0,
		RIGHT,
		DOWN,
		TOP
	};

	enum class lifeState_t
	{
		ALIVE = 0,
		DYING,
		DEAD
	};

	enum class state_t
	{
		NONE = -1,
		EXIT = cgf::EXIT_STATE,
		MENU = 0,
		PLAY
	};

	enum class entityID_t
	{
		UNINITIALIZED = -1,
		BACKGROUND = 0,
		BORDER,

		PLAYER,
		PLAYER_BASE,
		ENEMY,

		BULLET_ENEMY,
		BULLET_PLAYER,

		ENEMY_SPAWNER,

		BUTTON_START,
		BUTTON_OPTIONS,
		BUTTON_LEVEL_EDITOR,
		BUTTON_EXIT
	};

	enum class powerUpID_t
	{
		UNITIALIZED = -1,
		IMMORTAL = 0
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
