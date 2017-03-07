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

#include <Logger.hpp>
#include <State.hpp>

#include "Border.hpp"
#include "Background.hpp"
#include "GameConfig.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"
#include "Player.hpp"
#include "PhysicsChecker.hpp"

namespace kd
{
	class PlayState final :
		public cgf::State
	{
	public:
		PlayState( window_t* window ) :
			cgf::State( window ),
			exit( false )
		{}

		void OnStart() override;
		void OnStop() override;
		state_id_t Run() override;

		void UpdateThread( seconds_t dt, window_t& w ) override;

	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::shared_ptr<Player> playerPointer;
		std::map<entityID_t, std::shared_ptr<sf::Texture>> textures;

		sf::Font font;
		sf::Text healthText[3];
		sf::Text armorText;
		sf::Text baseHealthText;

		PhysicsChecker physicsChecker;

		bool exit;

		void unlockWindowContext() override { windowPtr->setActive( true ); }
		void lockWindowContext() override { windowPtr->setActive( false ); }

		void updateUI();
		void removeUnusedEntities();

		state_t processEvents( sf::Event& ev );
		void update( seconds_t dt );
		void draw();
	};
}