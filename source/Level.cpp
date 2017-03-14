/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "Level.hpp"

namespace kd
{
	bool Level::Load( const std::string& path )
	{
		cgf::Logger::Log( "Level loading started..." );

		std::ifstream levelFile( path, std::ios::binary );
		if ( !levelFile.good() )
		{
			cgf::Logger::Log( "Level loading error - cannot open file", cgf::Logger::ERROR );
			return false;
		}
		levelFile.read( reinterpret_cast<char*>( &this->levelData ), sizeof( internal::levelData_t ) );

		cgf::Logger::Log( "Level loading finished" );

		this->checkLevelData();
		this->initializeEntities();

		return true;
	}

	void Level::Save( const std::string& path )
	{
		cgf::Logger::Log( "Level saving started..." );

		std::ofstream levelFile( path, std::ios::binary | std::ios::trunc );
		levelFile.write( reinterpret_cast<char*>( &this->levelData ), sizeof( internal::levelData_t ) );

		cgf::Logger::Log( "Level saving finished" );
	}

	void Level::InitializeTextures( std::map<entityID_t, std::shared_ptr<sf::Texture>>* textures )
	{
		for ( auto t : *textures )
			if ( t.first == entityID_t::BACKGROUND )
				t.second.reset();

		( *textures )[entityID_t::BACKGROUND] = std::make_shared<sf::Texture>();
		if ( !( *textures )[entityID_t::BACKGROUND]->loadFromFile( this->levelData.backgroundTexturePath ) )
		{
			cgf::Logger::Log( "Cannot load BACKGROUND texture ('" + this->levelData.backgroundTexturePath + "')", cgf::Logger::ERROR );
			( *textures )[entityID_t::BACKGROUND].reset();
		}
		else
			this->background->SetTexture( ( *textures )[entityID_t::BACKGROUND] );
	}

	void Level::InitializePlayer( std::shared_ptr<Player> player )
	{
		player->SetPosition( this->levelData.playerSpawnPosition );
	}

	void Level::AddEntities( std::vector<std::shared_ptr<Entity>>* entitiesPtr, CollisionChecker* collisionCheckerPtr )
	{
		for ( auto border : this->borders )
			entitiesPtr->push_back( border );

		for ( auto spawner : this->spawners )
			entitiesPtr->push_back( spawner );

		entitiesPtr->push_back( this->background );
		this->background->SetDrawLayer( 0 );

		for ( auto border : this->borders )
			collisionCheckerPtr->AddBoxCollider( border );
	}

	void Level::RemoveEntities()
	{
		for ( auto border : this->borders )
			border->SetWishDelete( true );

		for ( auto spawner : this->spawners )
			spawner->SetWishDelete( true );

		this->background->SetWishDelete( true );

		this->borders.clear();
		this->spawners.clear();
		this->background.reset();
	}

	void Level::checkLevelData()
	{
		if ( this->levelData.playerSpawnPosition == sf::Vector2f( 0.0f, 0.0f ) )
			cgf::Logger::Log( "LevelData player spawn position is x(0) y(0) - possible error", cgf::Logger::WARNING );

		if ( this->levelData.bordersRects.size() == 0 )
			cgf::Logger::Log( "LevelData has no border collisions rects - possible error", cgf::Logger::WARNING );

		if ( this->levelData.spawnersData.size() == 0 )
			cgf::Logger::Log( "LevelData has no spawner data - possible error", cgf::Logger::WARNING );

		if ( this->levelData.backgroundTexturePath.size() <= 3 )
			cgf::Logger::Log( "Level data has short background texture path ('" + this->levelData.backgroundTexturePath + "') - possible error", cgf::Logger::WARNING );
	}

	void Level::initializeEntities()
	{
		this->RemoveEntities();

		for ( auto& border : this->levelData.bordersRects )
		{
			this->borders.push_back( std::make_shared<Border>() );
			this->borders.back()->SetType( entityID_t::BORDER );
			this->borders.back()->rectangle = border;
		}

		for ( auto& spawnerData : this->levelData.spawnersData )
		{
			this->spawners.push_back( std::make_shared<EnemySpawner>() );
			this->spawners.back()->SetType( entityID_t::ENEMY_SPAWNER );
			this->spawners.back()->SetSpawningTime( spawnerData.spawnTime );
			this->spawners.back()->SetStartVelocity( spawnerData.velocityDirection );
			this->spawners.back()->SetPosition( spawnerData.position );
		}

		this->background = std::make_shared<Background>();
	}
}