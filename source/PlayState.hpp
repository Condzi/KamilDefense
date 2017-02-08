/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include <Logger.hpp>
#include <State.hpp>

#include "GameConfig.hpp"
#include "Entity.hpp"

namespace kd
{
	class PlayState final : 
		public cgf::State
	{
	private:
		void unlockWindowContext() override { windowPtr->setActive(true); }
		void lockWindowContext() override { windowPtr->setActive(false); }

	public:
		PlayState(window_t* window) : 
			cgf::State(window)
		{}

		void onStart() override;
		void onStop() override;
		state_id_t run() override;

		void updateThread(seconds_t dt, window_t& w) override;

	private:
		std::vector<Entity> entities;
		// Player* player;
	};
}