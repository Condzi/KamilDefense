/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <framework/StateMachine.hpp>

#include "GameConfig.hpp"
#include "states/PlayState.hpp"
#include "states/MenuState.hpp"

#include "Settings.hpp"

int main()
{

	cgf::Logger::Initialize();
	kd::SETTINGS.Load( "GameSettings.ini" );
	kd::ResourceHolder::Initialize();

	window_t window( { kd::WINDOW_SIZE.x, kd::WINDOW_SIZE.y }, kd::WINDOW_TITLE );
	window.setFramerateLimit( kd::FPS_LIMIT );

	cgf::StateMachine stateMachine( static_cast<int16_t>( kd::state_t::MENU ) );

	stateMachine.RegisterState<kd::MenuState>( static_cast<int16_t>( kd::state_t::MENU ), &window );
	stateMachine.RegisterState<kd::PlayState>( static_cast<int16_t>( kd::state_t::PLAY ), &window );

	stateMachine.Run();

	kd::ResourceHolder::Shutdown();
	cgf::Logger::Shutdown();

	return 0;
}
