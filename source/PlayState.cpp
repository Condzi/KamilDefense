/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PlayState.hpp"

namespace kd
{
	void PlayState::updateUI()
	{
		auto hp = playerPointer->getHealth();

		if (hp >= 100)
			healthText[2].setString(sf::String(std::to_string(hp)[2]));
		else
			healthText[2].setString("-");

		if (hp >= 10)
			healthText[1].setString(sf::String(std::to_string(hp)[1]));
		else
			healthText[1].setString("-");

		healthText[0].setString(sf::String(std::to_string(hp)[0]));

		armorText.setString(std::to_string(playerPointer->getArmor()));

		baseHealthText.setString("0");
	}

	void PlayState::removeUnusedEntities()
	{
		for (auto it = entities.begin(); it != entities.end();)
		{
			if ((*it)->isWishingDelete())
				it = entities.erase(it);
			else
				it++;
		}
	}

	void PlayState::onStart()
	{
		startThread();

		if (!font.loadFromFile(FONT))
			cgf::Logger::log("Cannot load font file!", cgf::Logger::ERROR);
		else
		{
			healthText[0].setFont(font);
			healthText[1].setFont(font);
			healthText[2].setFont(font);

			armorText.setFont(font);

			baseHealthText.setFont(font);
		}

		{
			healthText[0].setCharacterSize(static_cast<uint32_t>(6 * SCALE));
			healthText[1].setCharacterSize(static_cast<uint32_t>(6 * SCALE));
			healthText[2].setCharacterSize(static_cast<uint32_t>(6 * SCALE));

			armorText.setCharacterSize(static_cast<uint32_t>(6 * SCALE));

			baseHealthText.setCharacterSize(static_cast<uint32_t>(6 * SCALE));
		}

		{
			healthText[0].setPosition(64.5f * SCALE, 0);
			healthText[1].setPosition(64.5f * SCALE, 5 * SCALE);
			healthText[2].setPosition(64.5f * SCALE, 10 * SCALE);

			armorText.setPosition(1 * SCALE, 62 * SCALE);
			
			baseHealthText.setPosition(64 * SCALE, 62 * SCALE);
		}
		
		// Loading textures
		{
			textures.emplace_back();
			textures.back().loadFromMemory(new sf::Texture);
			textures.back().get()->loadFromFile(PLAYER_TEXTURE);
			textures.back().setUniqueID(static_cast<unique_resource_id_t>(ENTITY_ID::PLAYER));

			textures.emplace_back();
			textures.back().loadFromMemory(new sf::Texture);
			textures.back().get()->loadFromFile(BACKGROUND_TEXTURE);
			textures.back().setUniqueID(static_cast<unique_resource_id_t>(ENTITY_ID::BACKGROUND));
		}

		auto bg = std::make_shared<Background>();
		auto player = std::make_shared<Player>();

		// Initializing player
		{
			playerPointer = player;

			player->setHealth(MAX_HEALTH);
			player->setArmor(MAX_ARMOR);

			bool found = false;
			for(auto& t : textures)
				if (t.getUniqueID() == static_cast<unique_resource_id_t>(ENTITY_ID::PLAYER))
				{
					found = true;
					player->setTexture(t.get());
				}

			if (!found)
				cgf::Logger::log("Cannot find PLAYER texture!", cgf::Logger::ERROR);

			player->setPosition({ static_cast<float>(WINDOW_SIZE.x / 2), static_cast<float>(WINDOW_SIZE.y / 2) });
			player->setMovementKeys(movement_keys_t(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space));
			player->setMovementForces(movement_forces_t(-250.f, 250.f, -500.f));
		}	
		
		// Initializing bg
		{
			bool found = false;
			for(auto& t : textures)
				if (t.getUniqueID() == static_cast<unique_resource_id_t>(ENTITY_ID::BACKGROUND))
				{
					found = true;
					bg->setTexture(t.get());
				}

			if (!found)
				cgf::Logger::log("Cannot find BACKGROUND texture!", cgf::Logger::ERROR);
		}

		entities.push_back(bg);
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

			removeUnusedEntities();

			updateUI();

			windowPtr->clear(sf::Color(100, 100, 100));

			for (auto& e : entities)
				e->draw(*windowPtr);

			windowPtr->draw(healthText[0]);
			windowPtr->draw(healthText[1]);
			windowPtr->draw(healthText[2]);
			windowPtr->draw(armorText);
			windowPtr->draw(baseHealthText);


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
		rectangle.setPosition(static_cast<float>(WINDOW_SIZE.x / 2), static_cast<float>(WINDOW_SIZE.y / 2));
		rectangle.setSize(sf::Vector2f(static_cast<float>(WINDOW_SIZE.x / 2), static_cast<float>(WINDOW_SIZE.y / 2)));
		rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

		rectangle.rotate(90 * dt);
		static uint32_t i = 1;

		rectangle.setScale(std::fabs(std::sinf(i * 3.14f / 180.f)), std::fabs(std::sinf(i * 3.14f / 180.f)));
		i++;

		w.clear(sf::Color(100,100,100));
		w.draw(rectangle);
		w.display();

		cgf::Logger::log("Thread update...", cgf::Logger::INFO, cgf::Logger::CONSOLE);
	}
}