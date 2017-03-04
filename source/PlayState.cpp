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
		auto testEnemy = std::make_shared<Enemy>();
		testEnemy->SetType( entityID_t::ENEMY );

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
			player->SetMovementForces( movementForces_t( -250.f, 250.f, -500.f ) );
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

		// test enemy
		{
			testEnemy->SetHealth( 100 );

			bool found = false;
			for ( auto& t : this->textures )
				if ( t.first == entityID_t::ENEMY )
				{
					found = true;
					testEnemy->SetTexture( t.second );
				}

			if ( !found )
				cgf::Logger::Log( "Cannot find ENEMY texture!", cgf::Logger::ERROR );

			testEnemy->SetPosition( { 0.0f,0.0f } );
		}


		auto borderWallDown = std::make_shared<Border>();
		borderWallDown->SetType( entityID_t::BORDER );
		borderWallDown->SetPosition( { 0, 31 * 2 * SCALE } );
		borderWallDown->rectangle.width = 32 * 2 * SCALE;
		borderWallDown->rectangle.height = 1.f;

		auto borderWallRight = std::make_shared<Border>();
		borderWallRight->SetType( entityID_t::BORDER );
		borderWallRight->SetPosition( { 32 * 2 * SCALE, 0 } );
		borderWallRight->rectangle.width = 1.f;
		borderWallRight->rectangle.height = 32 * 2 * SCALE;

		auto borderWallLeft = std::make_shared<Border>();
		borderWallLeft->SetType( entityID_t::BORDER );
		borderWallLeft->SetPosition( { -1.0f, 0.0f } );
		borderWallLeft->rectangle.width = 1.f;
		borderWallLeft->rectangle.height = 32 * 2 * SCALE;

		auto borderPlatformLeft = std::make_shared<Border>();
		borderPlatformLeft->SetType( entityID_t::BORDER );
		borderPlatformLeft->SetPosition( { 0.0f, 21 * SCALE * 2 } );
		borderPlatformLeft->rectangle.width = 8 * SCALE * 2;
		borderPlatformLeft->rectangle.height = 1 * SCALE * 2;

		auto borderPlatformMiddle = std::make_shared<Border>();
		borderPlatformMiddle->SetType( entityID_t::BORDER );
		borderPlatformMiddle->SetPosition( { 11.0f * 2 * SCALE, 15 * SCALE * 2 } );
		borderPlatformMiddle->rectangle.width = 10 * SCALE * 2;
		borderPlatformMiddle->rectangle.height = 1 * SCALE * 2;

		auto borderPlatformRight = std::make_shared<Border>();
		borderPlatformRight->SetType( entityID_t::BORDER );
		borderPlatformRight->SetPosition( { 24 * 2 * SCALE, 21 * SCALE * 2 } );
		borderPlatformRight->rectangle.width = 8 * SCALE * 2;
		borderPlatformRight->rectangle.height = 1 * SCALE * 2;

		this->entities.push_back( bg );
		this->entities.push_back( player );
		this->entities.push_back( borderWallDown );
		this->entities.push_back( borderWallRight );
		this->entities.push_back( borderWallLeft );
		this->entities.push_back( borderPlatformLeft );
		this->entities.push_back( borderPlatformMiddle );
		this->entities.push_back( borderPlatformRight );
		this->entities.push_back( testEnemy );

		this->physicsChecker.AddBoxCollider( player );
		this->physicsChecker.AddBoxCollider( borderWallDown );
		this->physicsChecker.AddBoxCollider( borderWallRight );
		this->physicsChecker.AddBoxCollider( borderWallLeft );
		this->physicsChecker.AddBoxCollider( borderPlatformLeft );
		this->physicsChecker.AddBoxCollider( borderPlatformMiddle );
		this->physicsChecker.AddBoxCollider( borderPlatformRight );
		this->physicsChecker.AddBoxCollider( testEnemy );

		this->EndThread();
	}

	void PlayState::OnStop()
	{
		this->StartThread();

		this->playerPointer.reset();
		this->entities.clear();
		this->textures.clear();

		this->EndThread();
	}

	state_id_t PlayState::Run()
	{
		bool end = false;
		sf::Event event;

		while ( !end )
		{
			while ( this->windowPtr->pollEvent( event ) )
			{
				if ( event.type == sf::Event::Closed )
					return state_t::EXIT;

				if ( event.type == sf::Event::KeyReleased )
					if ( event.key.code == sf::Keyboard::Escape )
						end = true;
			}

			for ( auto& e : this->entities )
				e->Update( 1.f / FPS_LIMIT );

			this->removeUnusedEntities();

			this->updateUI();

			this->playerPointer->CheckEvents();
			this->physicsChecker.Update( 1.f / FPS_LIMIT );

			this->windowPtr->clear( sf::Color( 100, 100, 100 ) );

			for ( auto& e : this->entities )
				e->Draw( *this->windowPtr );

			this->windowPtr->draw( healthText[0] );
			this->windowPtr->draw( healthText[1] );
			this->windowPtr->draw( healthText[2] );
			this->windowPtr->draw( armorText );
			this->windowPtr->draw( baseHealthText );

			this->windowPtr->display();
		}

		// Change in future to ::MENU
		return state_t::EXIT;
	}

	void PlayState::UpdateThread( seconds_t dt, window_t& w )
	{
		static sf::RectangleShape rectangle;
		rectangle.setFillColor( sf::Color::Transparent );
		rectangle.setOutlineColor( sf::Color( 125, 125, 125 ) );
		rectangle.setOutlineThickness( 5.f );
		rectangle.setPosition( static_cast<float>( WINDOW_SIZE.x / 2 ), static_cast<float>( WINDOW_SIZE.y / 2 ) );
		rectangle.setSize( sf::Vector2f( static_cast<float>( WINDOW_SIZE.x / 2 ), static_cast<float>( WINDOW_SIZE.y / 2 ) ) );
		rectangle.setOrigin( rectangle.getSize().x / 2, rectangle.getSize().y / 2 );

		rectangle.rotate( 90 * dt );
		static uint32_t i = 1;

		rectangle.setScale( std::fabs( std::sinf( i * 3.14f / 180.f ) ), std::fabs( std::sinf( i * 3.14f / 180.f ) ) );
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
}