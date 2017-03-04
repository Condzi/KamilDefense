/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <StateMachine.hpp>

#include "GameConfig.hpp"
#include "PlayState.hpp"

int main()
{
	cgf::Logger::Initialize();

	window_t window( { kd::WINDOW_SIZE.x, kd::WINDOW_SIZE.y }, kd::WINDOW_TITLE );
	window.setFramerateLimit( kd::FPS_LIMIT );

	cgf::StateMachine stateMachine;

	stateMachine.RegisterState<kd::PlayState>( static_cast<state_id_t>( kd::state_t::MENU ), &window );

	stateMachine.Run();

	cgf::Logger::Shutdown();

	return 0;
}