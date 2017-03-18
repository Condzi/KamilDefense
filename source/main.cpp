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
	kd::ResourceHolder::Initialize();

	window_t window( { kd::WINDOW_SIZE.x, kd::WINDOW_SIZE.y }, kd::WINDOW_TITLE );
	window.setFramerateLimit( kd::FPS_LIMIT );

	cgf::StateMachine stateMachine;

	stateMachine.RegisterState<kd::PlayState>( static_cast<int16_t>( kd::state_t::MENU ), &window );

	stateMachine.Run();

	kd::ResourceHolder::Shutdown();
	cgf::Logger::Shutdown();

	return 0;
}