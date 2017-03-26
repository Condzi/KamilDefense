/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <framework/StateMachine.hpp>

#include "states/PlayState.hpp"
#include "states/MenuState.hpp"

int main()
{
	cgf::Logger::Initialize();
	kd::SETTINGS.Load( "GameSettings.ini" );
	kd::ResourceHolder::Initialize();

	uint32_t x = kd::SETTINGS.GLOBAL.WINDOW_SIZE_X * kd::SETTINGS.GAMEPLAY.SCALE;
	uint32_t y = kd::SETTINGS.GLOBAL.WINDOW_SIZE_Y * kd::SETTINGS.GAMEPLAY.SCALE;

	window_t window( sf::VideoMode( x, y ), kd::SETTINGS.INTERNAL.WINDOW_TITLE );
	window.setFramerateLimit( kd::SETTINGS.GLOBAL.FPS_LIMIT );

	cgf::StateMachine stateMachine( static_cast<int16_t>( kd::state_t::MENU ) );

	stateMachine.RegisterState<kd::MenuState>( static_cast<int16_t>( kd::state_t::MENU ), &window );
	stateMachine.RegisterState<kd::PlayState>( static_cast<int16_t>( kd::state_t::PLAY ), &window );

	stateMachine.Run();

	kd::ResourceHolder::Shutdown();
	cgf::Logger::Shutdown();

	return 0;
}
