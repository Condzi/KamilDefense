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
	constexpr float SCALE = 10.0f;
	constexpr float GRAVITY = 10.0f;
	constexpr float OBJECT_WEIGHT = 50.0f;

	constexpr auto WINDOW_TITLE = "Kamil Defense";
	struct
	{
		static constexpr uint16_t x = static_cast<uint16_t>( ( 64 + 3 ) * SCALE );
		static constexpr uint16_t y = static_cast<uint16_t>( ( 64 + 5 ) * SCALE );
	} static constexpr WINDOW_SIZE;
	constexpr uint32_t FPS_LIMIT = 64;

	constexpr uint8_t MAX_HEALTH = 200;
	constexpr uint8_t MAX_ARMOR = 100;
	constexpr seconds_t DAMAGE_BLOCK_TIME = 0.32f;
	constexpr seconds_t ENEMY_SHOOT_COOLDOWN = 0.5f;
	constexpr float PLAYER_MISSILE_SPEED = 750.0f;
	constexpr float ENEMY_MISSILE_SPEED = 375.0f;

	constexpr auto FONT_PATH = "data/fonts/wendy.ttf";
	constexpr auto PLAYER_TEXTURE_PATH = "data/textures/player.png";
	constexpr auto ENEMY_TEXTURE_PATH = "data/textures/enemy.png";
	constexpr auto BACKGROUND_TEXTURE_PATH = "data/textures/base.png";
}