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
#include "entities/EntityManager.hpp"
#include "entities/Enemy.hpp"
#include "entities/EnemySpawner.hpp"
#include "Settings.hpp"
#include "gameUtil/Level.hpp"
#include "ResourceHolder.hpp"
#include "entities/Player.hpp"

#include "entities/poweUps/Immortality.hpp"

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
		EntityManager entityManager;
		std::weak_ptr<Player> playerPointer;
		CollisionChecker collisionChecker;
		Level level;
		sf::View playerView;

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

		state_t processEvents( sf::Event& ev );
		void update( seconds_t dt );
		void draw();
		void updateUIposition();
		void setLevelBackgroundAsCenterOfView();
	};
}