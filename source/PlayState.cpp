/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PlayState.hpp"

namespace kd
{
	void PlayState::onStart()
	{
		startThread();
		/*
			Initialize Entities and add them to Renderer here
		*/
		endThread();
	}

	void PlayState::onStop()
	{
		startThread();

		entities.clear();
	
		endThread();
	}

	state_id_t PlayState::run()
	{
		bool end = false;
		sf::Event event;

		while (!end)
		{
			while (windowPtr->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					return STATE_ID::EXIT;

				if (event.type == sf::Event::KeyReleased)
					if (event.key.code == sf::Keyboard::Escape)
						end = true;
			}

			for (auto& e : entities)
			{
				e.update(1.f / 60);
			}

			windowPtr->clear();
			// Renderer draw()
			windowPtr->display();
		}

		// Change in future to ::MENU
		return STATE_ID::EXIT;
	}

	void PlayState::updateThread(seconds_t dt, window_t& w)
	{
		cgf::Logger::log("Thread update...", cgf::Logger::INFO, cgf::Logger::CONSOLE);
	}
}