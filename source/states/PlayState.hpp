/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include <framework/Logger.hpp>
#include <framework/State.hpp>

#include "gameUtil/CollisionChecker.hpp"
#include "entities/Entity.hpp"
#include "entities/Enemy.hpp"
#include "entities/EnemySpawner.hpp"
#include "GameConfig.hpp"
#include "gameUtil/Level.hpp"
#include "ResourceHolder.hpp"
#include "entities/Player.hpp"

namespace kd
{
	class PlayState final :
		public cgf::State
	{
	public:
		PlayState( window_t* window ) :
			State( window ),
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

		CollisionChecker collisionChecker;

		Level level;

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

		std::pair<int8_t, int8_t> getDrawLayersInterval();
	};
}