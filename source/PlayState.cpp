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
			Initialize Entities here
		*/

		// Loading textures

		textures.emplace_back();
		textures.back().setCheckCount(true);
		textures.back().loadFromMemory(new sf::Texture);
		textures.back().get()->loadFromFile(PLAYER_TEXTURE);
		textures.back().setUniqueID(static_cast<unique_resource_id_t>(ENTITY_ID::PLAYER));
		
		// Making entities

		auto player = std::make_shared<Player>();
		// temporary I know that player texture is last
		player->setTexture(textures.back().get());

		player->setPosition({ static_cast<float>(WINDOW_SIZE.x / 2), static_cast<float>(WINDOW_SIZE.y / 2) });
		player->setMovementKeys(movement_keys_t(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space));
		player->setMovementForces(movement_forces_t(-250.f, 250.f, -500.f));
	
		entities.push_back(player);

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
				e->update(1.f / FPS_LIMIT);

			windowPtr->clear(sf::Color(100, 100, 100));

			for (auto& e : entities)
				e->draw(*windowPtr);

			windowPtr->display();
		}

		// Change in future to ::MENU
		return STATE_ID::EXIT;
	}

	void PlayState::updateThread(seconds_t dt, window_t& w)
	{
		static sf::RectangleShape rectangle;
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color(125, 125, 125));
		rectangle.setOutlineThickness(5.f);
		rectangle.setPosition(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
		rectangle.setSize(sf::Vector2f(WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2));
		rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

		rectangle.rotate(90 * dt);
		static uint32_t i = 1;

		rectangle.setScale(std::abs(std::sin(i * 3.14 / 180.f)), std::abs(std::sin(i * 3.14 / 180.f)));
		i++;

		w.clear(sf::Color(100,100,100));
		w.draw(rectangle);
		w.display();

		cgf::Logger::log("Thread update...", cgf::Logger::INFO, cgf::Logger::CONSOLE);
	}
}