/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include <framework/State.hpp>

#include "entities/Background.hpp"
#include "ResourceHolder.hpp"
#include "menuUtil/Button.hpp"

namespace kd
{
	class MenuState final :
		public cgf::State
	{
	public:
		MenuState( window_t* window ) :
			State( window ),
			exit( false )
		{}

		void OnStart() override;
		void OnStop() override;
		int16_t Run() override;

		void UpdateThread( seconds_t dt, window_t& w ) override
		{}

	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::vector<std::weak_ptr<Drawable>> drawables;

		bool exit;

		void unlockWindowContext() override
		{
			windowPtr->setActive( true );
		}
		void lockWindowContext() override
		{
			windowPtr->setActive( false );
		}

		void removeUnusedEntities();
		void updateDrawables();

		state_t processEvents( sf::Event& ev );
		void update( seconds_t dt );
		void draw();
		std::pair<int8_t, int8_t> getDrawLayersInterval();
	};
}