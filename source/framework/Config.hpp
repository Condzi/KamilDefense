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
// Use it instead of naming resources (create enum RESOURCES_ID {myResource = 1, other = 12} etc
using unique_resource_id_t = int16_t;
// Set this type to your window type. For example - if you are using SFML, set it to sf::RenderWindow
using window_t = sf::RenderWindow;

template<typename CONDITION>
using enable_if = typename std::enable_if<CONDITION::value>::type;

namespace CGF_NAMESPACE
{
	// If resource is still unsued after this time Resource will automaticly delete itself
	constexpr seconds_t RESOURCE_DELETE_TIME = 3.0f;
	// Max amount of handled resources (3565 for default) per one ResourceManager
	constexpr size_t MAX_RESOURCES = 0xded;

	// ID that never should be used to normal state - return this in State::Run if you want to exit State Machine
	constexpr int16_t EXIT_STATE = -0xded;

	static auto& LOGGER_STREAM = std::cout;

	constexpr char LOGGER_PREFIX[3] =
	{
		'?', '!', 'X'
	};

	constexpr auto LOG_FILE_PATH = "log.txt";
}
