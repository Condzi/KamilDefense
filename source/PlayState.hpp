/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <Resource.hpp>
#include <Logger.hpp>
#include <State.hpp>

#include "GameConfig.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Background.hpp"

namespace kd
{
	class PlayState final : 
		public cgf::State
	{
	private:
		void unlockWindowContext() override { windowPtr->setActive(true); }
		void lockWindowContext() override { windowPtr->setActive(false); }

		void updateUI();

	public:
		PlayState(window_t* window) : 
			cgf::State(window)
		{}

		void onStart() override;
		void onStop() override;
		state_id_t run() override;

		void updateThread(seconds_t dt, window_t& w) override;

	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::shared_ptr<Player> playerPointer;
		std::vector<cgf::Resource<sf::Texture>> textures;

		sf::Font font;
		sf::Text healthText[3];
		sf::Text armorText;
		sf::Text baseHealthText;		
	};
}