/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#define CGF_NAMESPACE cgf
#define CGF_PRIVATE priv

using seconds_t = float;
// Set this type to your window type. For example - if you are using SFML, set it to sf::RenderWindow
using window_t = sf::RenderWindow;

namespace CGF_NAMESPACE
{
	// ID that never should be used to normal state - return this in State::Run if you want to exit State Machine
	constexpr int16_t EXIT_STATE = -0xded;

	static auto& LOGGER_STREAM = std::cout;

	constexpr char LOGGER_PREFIX[3] =
	{
		'?', '!', 'X'
	};

	constexpr auto LOG_FILE_PATH = "log.txt";
}
