/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <StateMachine.hpp>

#include "GameConfig.hpp"
#include "PlayState.hpp"

int main()
{
	cgf::Logger::initialize();

	window_t window({ kd::WINDOW_SIZE.x, kd::WINDOW_SIZE.y }, kd::WINDOW_TITLE);
	window.setFramerateLimit(kd::FPS_LIMIT);

	cgf::StateMachine stateMachine;

	stateMachine.registerState<kd::PlayState>(static_cast<state_id_t>(kd::STATE_ID::MENU), &window);
	
	stateMachine.run();
	
	cgf::Logger::shutdown();

	return 0;
}