/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PlayState.hpp"

namespace kd
{
	void PlayState::OnStart()
	{
		this->StartThread();

		MissileManager::Initialize( &this->physicsChecker );

		if ( !this->font.loadFromFile( FONT ) )
			cgf::Logger::Log( "Cannot load font file!", cgf::Logger::ERROR );
		else
		{
			this->healthText[0].setFont( this->font );
			this->healthText[1].setFont( this->font );
			this->healthText[2].setFont( this->font );

			this->armorText.setFont( this->font );

			this->baseHealthText.setFont( this->font );
		}

		{
			this->healthText[0].setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
			this->healthText[1].setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
			this->healthText[2].setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );

			this->armorText.setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );

			this->baseHealthText.setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
		}

		{
			this->healthText[0].setPosition( 64.5f * SCALE, 0 );
			this->healthText[1].setPosition( 64.5f * SCALE, 5 * SCALE );
			this->healthText[2].setPosition( 64.5f * SCALE, 10 * SCALE );

			this->armorText.setPosition( 1 * SCALE, 62 * SCALE );

			this->baseHealthText.setPosition( 64 * SCALE, 62 * SCALE );
		}

		// Loading textures
		{
			this->textures[entityID_t::PLAYER] = std::make_shared<sf::Texture>();
			this->textures[entityID_t::PLAYER]->loadFromFile( PLAYER_TEXTURE );


			this->textures[entityID_t::BACKGROUND] = std::make_shared<sf::Texture>();
			this->textures[entityID_t::BACKGROUND]->loadFromFile( BACKGROUND_TEXTURE );

			this->textures[entityID_t::ENEMY] = std::make_shared<sf::Texture>();
			this->textures[entityID_t::ENEMY]->loadFromFile( ENEMY_TEXTURE );
		}

		auto bg = std::make_shared<Background>();
		bg->SetType( entityID_t::BACKGROUND );
		auto player = std::make_shared<Player>();
		player->SetType( entityID_t::PLAYER );
		auto enemySpawnerLeft = std::make_shared<EnemySpawner>();
		enemySpawnerLeft->SetType( entityID_t::ENEMY_SPAWNER );
		auto enemySpawnerRight = std::make_shared<EnemySpawner>();
		enemySpawnerRight->SetType( entityID_t::ENEMY_SPAWNER );

		{
			enemySpawnerLeft->SetEnemyTexture( this->textures[entityID_t::ENEMY] );
			enemySpawnerLeft->SetPosition( { 1 * 2 * SCALE, 10 * 2 * SCALE } );
			enemySpawnerLeft->SetPhysicChecker( &this->physicsChecker );
			enemySpawnerLeft->SetEntitiesVector( &this->entities );
			enemySpawnerLeft->SetStartVelocity( { 250.0f, -250.0f } );
			enemySpawnerLeft->SetSpawningTime( 5.0f );
		}
		
		{
			enemySpawnerRight->SetEnemyTexture( this->textures[entityID_t::ENEMY] );
			enemySpawnerRight->SetPosition( { 28 * 2 * SCALE, 10 * 2 * SCALE } );
			enemySpawnerRight->SetPhysicChecker( &this->physicsChecker );
			enemySpawnerRight->SetEntitiesVector( &this->entities );
			enemySpawnerRight->SetStartVelocity( { -250.0f, -250.0f } );
			enemySpawnerRight->SetSpawningTime( 5.0f );
		}

		// Initializing player
		{
			this->playerPointer = player;

			player->SetHealth( MAX_HEALTH );
			player->SetArmor( MAX_ARMOR );

			bool found = false;
			for ( auto& t : this->textures )
				if ( t.first == entityID_t::PLAYER )
				{
					found = true;
					player->SetTexture( t.second );
				}

			if ( !found )
				cgf::Logger::Log( "Cannot find PLAYER texture!", cgf::Logger::ERROR );

			player->SetPosition( { static_cast<float>( WINDOW_SIZE.x / 2 ), static_cast<float>( WINDOW_SIZE.y / 2 ) } );
			player->SetMovementKeys( movementKeys_t( sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space ) );
			player->SetMovementForces( movementForces_t( -250.0f, 250.0f, -500.0f ) );
		}

		// Initializing bg
		{
			bool found = false;
			for ( auto& t : this->textures )
				if ( t.first == entityID_t::BACKGROUND )
				{
					found = true;
					bg->SetTexture( t.second );
				}

			if ( !found )
				cgf::Logger::Log( "Cannot find BACKGROUND texture!", cgf::Logger::ERROR );
		}



		auto borderWallDown = std::make_shared<Border>();
		borderWallDown->SetType( entityID_t::BORDER );
		borderWallDown->SetPosition( { 0, 31 * 2 * SCALE } );
		borderWallDown->rectangle.width = 32 * 2 * SCALE;
		borderWallDown->rectangle.height = 2.0f * SCALE;

		auto borderWallRight = std::make_shared<Border>();
		borderWallRight->SetType( entityID_t::BORDER );
		borderWallRight->SetPosition( { 32 * 2 * SCALE, 0 } );
		borderWallRight->rectangle.width = 2.0f * SCALE;
		borderWallRight->rectangle.height = 32 * 2 * SCALE;

		auto borderWallLeft = std::make_shared<Border>();
		borderWallLeft->SetType( entityID_t::BORDER );
		borderWallLeft->SetPosition( { -( 2.0f * SCALE ) , 0.0f } );
		borderWallLeft->rectangle.width = 2.0f * SCALE;
		borderWallLeft->rectangle.height = 32 * 2 * SCALE;

		auto borderPlatformLeft = std::make_shared<Border>();
		borderPlatformLeft->SetType( entityID_t::BORDER );
		borderPlatformLeft->SetPosition( { 0.0f, 21 * SCALE * 2 } );
		borderPlatformLeft->rectangle.width = 8 * SCALE * 2;
		borderPlatformLeft->rectangle.height = 2.0f * SCALE;;

		auto borderPlatformMiddle = std::make_shared<Border>();
		borderPlatformMiddle->SetType( entityID_t::BORDER );
		borderPlatformMiddle->SetPosition( { 11.0f * 2 * SCALE, 15 * SCALE * 2 } );
		borderPlatformMiddle->rectangle.width = 10 * SCALE * 2;
		borderPlatformMiddle->rectangle.height = 2.0f * SCALE;;

		auto borderPlatformRight = std::make_shared<Border>();
		borderPlatformRight->SetType( entityID_t::BORDER );
		borderPlatformRight->SetPosition( { 24 * 2 * SCALE, 21 * SCALE * 2 } );
		borderPlatformRight->rectangle.width = 8 * SCALE * 2;
		borderPlatformRight->rectangle.height = 2.0f * SCALE;;

		this->entities.push_back( enemySpawnerLeft );
		this->entities.push_back( enemySpawnerRight );
		this->entities.push_back( bg );
		this->entities.push_back( player );
		this->entities.push_back( borderWallDown );
		this->entities.push_back( borderWallRight );
		this->entities.push_back( borderWallLeft );
		this->entities.push_back( borderPlatformLeft );
		this->entities.push_back( borderPlatformMiddle );
		this->entities.push_back( borderPlatformRight );

		this->physicsChecker.AddBoxCollider( player );
		this->physicsChecker.AddBoxCollider( borderWallDown );
		this->physicsChecker.AddBoxCollider( borderWallRight );
		this->physicsChecker.AddBoxCollider( borderWallLeft );
		this->physicsChecker.AddBoxCollider( borderPlatformLeft );
		this->physicsChecker.AddBoxCollider( borderPlatformMiddle );
		this->physicsChecker.AddBoxCollider( borderPlatformRight );

		this->EndThread();
	}

	void PlayState::OnStop()
	{
		this->StartThread();

		this->playerPointer.reset();
		this->entities.clear();
		this->textures.clear();
		MissileManager::Shutdown();

		this->EndThread();
	}

	state_id_t PlayState::Run()
	{
		sf::Event event;

		while ( !this->exit )
		{
			this->removeUnusedEntities();

			state_t stateToSwitch = this->processEvents( event );

			if ( stateToSwitch != state_t::NONE )
			{
				return static_cast<state_id_t>( stateToSwitch );
			}

			this->update( 1.0f / FPS_LIMIT );

			this->draw();
		}

		// Change in future to ::MENU
		return state_t::EXIT;
	}

	void PlayState::UpdateThread( seconds_t dt, window_t& w )
	{
		static sf::RectangleShape rectangle;
		rectangle.setFillColor( sf::Color::Transparent );
		rectangle.setOutlineColor( sf::Color( 125, 125, 125 ) );
		rectangle.setOutlineThickness( 5.0f );
		rectangle.setPosition( static_cast<float>( WINDOW_SIZE.x / 2 ), static_cast<float>( WINDOW_SIZE.y / 2 ) );
		rectangle.setSize( sf::Vector2f( static_cast<float>( WINDOW_SIZE.x / 2 ), static_cast<float>( WINDOW_SIZE.y / 2 ) ) );
		rectangle.setOrigin( rectangle.getSize().x / 2, rectangle.getSize().y / 2 );

		rectangle.rotate( 90 * dt );
		static uint32_t i = 1;

		rectangle.setScale( std::fabs( std::sinf( i * 3.14f / 180.0f ) ), std::fabs( std::sinf( i * 3.14f / 180.0f ) ) );
		i++;

		w.clear( sf::Color( 100, 100, 100 ) );
		w.draw( rectangle );
		w.display();

		cgf::Logger::Log( "Thread update...", cgf::Logger::INFO, cgf::Logger::CONSOLE );
	}


	void PlayState::updateUI()
	{
		auto hp = this->playerPointer->GetHealth();

		if ( hp >= 100 )
			this->healthText[2].setString( sf::String( std::to_string( hp )[2] ) );
		else
			this->healthText[2].setString( "-" );

		if ( hp >= 10 )
			this->healthText[1].setString( sf::String( std::to_string( hp )[1] ) );
		else
			this->healthText[1].setString( "-" );

		this->healthText[0].setString( sf::String( std::to_string( hp )[0] ) );

		this->armorText.setString( std::to_string( playerPointer->GetArmor() ) );

		this->baseHealthText.setString( "0" );
	}

	void PlayState::removeUnusedEntities()
	{
		for ( auto it = this->entities.begin(); it != this->entities.end();)
		{
			if ( ( *it )->IsWishingDelete() )
				it = this->entities.erase( it );
			else
				it++;
		}
	}

	state_t PlayState::processEvents( sf::Event& ev )
	{
		while ( this->windowPtr->pollEvent( ev ) )
		{
			if ( ev.type == sf::Event::Closed )
				return state_t::EXIT;

			if ( ev.type == sf::Event::KeyReleased )
				if ( ev.key.code == sf::Keyboard::Escape )
					this->exit = true;
		}

		return state_t::NONE;
	}

	void PlayState::update( seconds_t dt )
	{
		for ( size_t i = 0; i < this->entities.size(); i++ )
			this->entities[i]->Update( dt );

		this->physicsChecker.Update( 1.0f / FPS_LIMIT );
	
		this->updateUI();

		MissileManager::Update( 1.0f / FPS_LIMIT );
	}

	void PlayState::draw()
	{

		this->windowPtr->clear( sf::Color( 100, 100, 100 ) );

		for ( auto& e : this->entities )
			e->Draw( *this->windowPtr );

		this->windowPtr->draw( healthText[0] );
		this->windowPtr->draw( healthText[1] );
		this->windowPtr->draw( healthText[2] );
		this->windowPtr->draw( armorText );
		this->windowPtr->draw( baseHealthText );
		MissileManager::Draw( *this->windowPtr );

		this->windowPtr->display();
	}
}