/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

#include <Config.hpp>

namespace kd
{
	// Sprites are very small so they must be scaled up
	constexpr float SCALE = 10.f;

	constexpr auto WINDOW_TITLE = "Kamil Defense";
	constexpr struct
	{
		uint16_t x = 64 * SCALE;
		uint16_t y = 64 * SCALE;
	}WINDOW_SIZE;
	constexpr uint32_t FPS_LIMIT = 64;

	enum STATE_ID
	{
		EXIT = cgf::EXIT_STATE,
		Menu = 0,
		Play
	};
}