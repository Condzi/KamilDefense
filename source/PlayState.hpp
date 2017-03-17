/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include <Logger.hpp>
#include <State.hpp>

#include "Border.hpp"
#include "Background.hpp"
#include "CollisionChecker.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "EnemySpawner.hpp"
#include "GameConfig.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"

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
		int16_t Run() override;

		void UpdateThread( seconds_t dt, window_t& w ) override;

	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::vector<std::weak_ptr<Drawable>> drawables;
		std::weak_ptr<Player> playerPointer;
		//std::map<entityID_t, std::shared_ptr<sf::Texture>> textures;

		//sf::Font font;
		//sf::Text healthText[3];
		//sf::Text armorText;
		//sf::Text baseHealthText;

		CollisionChecker physicsChecker;

		bool exit;

		void unlockWindowContext() override 
		{ 
			windowPtr->setActive( true ); 
		}
		void lockWindowContext() override 
		{ 
			windowPtr->setActive( false ); 
		}

		void updateUI();
		void removeUnusedEntities();
		void updateDrawables();

		state_t processEvents( sf::Event& ev );
		void update( seconds_t dt );
		void draw();
	};
}