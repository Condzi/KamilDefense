/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <fstream>
#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Background.hpp"
#include "Border.hpp"
#include "CollisionChecker.hpp"
#include "Entity.hpp"
#include "EnemySpawner.hpp"

namespace kd
{
	namespace internal
	{
		struct enemySpawnerData_t
		{
			sf::Vector2f position;
			sf::Vector2f velocityDirection;
			seconds_t spawnTime;

			enemySpawnerData_t( const sf::Vector2f& pos = { 0.0f, 0.0f }, const sf::Vector2f& velDir = { 0.0f, 0.0f }, seconds_t sTime = 0.0f ) :
				position( pos ),
				velocityDirection( velDir ),
				spawnTime( sTime )
			{}
		};

		struct levelData_t final
		{
			sf::Vector2f playerSpawnPosition = { 0.0f, 0.0f };
			std::vector<sf::FloatRect> bordersRects;
			std::vector<internal::enemySpawnerData_t> spawnersData;
			std::string backgroundTexturePath = "";
			// Base rect...
		};
	}



	class Level final
	{
	public:
		Level()
		{}


		void SetLevelData( internal::levelData_t& lvlData )
		{
			this->levelData = lvlData;
		}

		internal::levelData_t& GetLEvelData()
		{
			return this->levelData;
		}

		bool Load( const std::string& path );
		void Save( const std::string& path );
		// In future - maybe pass pointer to entityID_t::BACKGROUND only?
		void InitializeTextures( std::map<entityID_t, std::shared_ptr<sf::Texture>>* textures );
		void InitializePlayer( std::shared_ptr<Player> player );

		void AddEntities( std::vector<std::shared_ptr<Entity>>* entitiesPtr, CollisionChecker* collisionCheckerPtr );
		// Removes Entities (Borders, Spawners and Background) from PlayState Entity vector and CollisionChecker - just simply mark them as WishDelete.
		void RemoveEntities();

	private:
		internal::levelData_t levelData;

		std::vector<std::shared_ptr<Border>> borders;
		std::vector<std::shared_ptr<EnemySpawner>> spawners;
		std::shared_ptr<Background> background;

		void checkLevelData();
		void initializeEntities();
	};
}
