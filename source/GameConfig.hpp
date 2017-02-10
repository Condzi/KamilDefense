/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

#include <Config.hpp>

namespace kd
{
	constexpr bool DEBUG_DRAW_BORDERS = true;

	// Sprites are very small so they must be scaled up
	constexpr float SCALE = 10.f;
	constexpr float GRAVITY = 100.f;

	constexpr auto WINDOW_TITLE = "Kamil Defense";
	constexpr struct
	{
		uint16_t x = static_cast<uint16_t>((64 + 3) * SCALE);
		uint16_t y = static_cast<uint16_t>((64 + 5) * SCALE);
	}WINDOW_SIZE;
	constexpr uint32_t FPS_LIMIT = 64;

	constexpr uint8_t MAX_HEALTH = 200;
	constexpr uint8_t MAX_ARMOR = 100;

	constexpr auto FONT = "data/fonts/wendy.ttf";
	constexpr auto PLAYER_TEXTURE = "data/textures/player.png";
	constexpr auto BACKGROUND_TEXTURE = "data/textures/base.png";

	enum STATE_ID
	{
		EXIT = cgf::EXIT_STATE,
		MENU = 0,
		PLAY
	};

	enum ENTITY_ID
	{
		BACKGROUND = 0,

		PLAYER,
		ENEMY,

		BULLET
	};
}