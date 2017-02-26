/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PlayState.hpp"

namespace kd
{
	void PlayState::updateUI()
	{
		auto hp = playerPointer->GetHealth();

		if ( hp >= 100 )
			healthText[2].setString( sf::String( std::to_string( hp )[2] ) );
		else
			healthText[2].setString( "-" );

		if ( hp >= 10 )
			healthText[1].setString( sf::String( std::to_string( hp )[1] ) );
		else
			healthText[1].setString( "-" );

		healthText[0].setString( sf::String( std::to_string( hp )[0] ) );

		armorText.setString( std::to_string( playerPointer->GetArmor() ) );

		baseHealthText.setString( "0" );
	}

	void PlayState::removeUnusedEntities()
	{
		for ( auto it = entities.begin(); it != entities.end();)
		{
			if ( ( *it )->IsWishingDelete() )
				it = entities.erase( it );
			else
				it++;
		}
	}

	void PlayState::onStart()
	{
		startThread();

		if ( !font.loadFromFile( FONT ) )
			cgf::Logger::log( "Cannot load font file!", cgf::Logger::ERROR );
		else
		{
			healthText[0].setFont( font );
			healthText[1].setFont( font );
			healthText[2].setFont( font );

			armorText.setFont( font );

			baseHealthText.setFont( font );
		}

		{
			healthText[0].setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
			healthText[1].setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
			healthText[2].setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );

			armorText.setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );

			baseHealthText.setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
		}

		{
			healthText[0].setPosition( 64.5f * SCALE, 0 );
			healthText[1].setPosition( 64.5f * SCALE, 5 * SCALE );
			healthText[2].setPosition( 64.5f * SCALE, 10 * SCALE );

			armorText.setPosition( 1 * SCALE, 62 * SCALE );

			baseHealthText.setPosition( 64 * SCALE, 62 * SCALE );
		}

		// Loading textures
		{
			textures.emplace_back();
			textures.back().loadFromMemory( new sf::Texture );
			textures.back().get()->loadFromFile( PLAYER_TEXTURE );
			textures.back().setUniqueID( static_cast<unique_resource_id_t>( entityID_t::PLAYER ) );

			textures.emplace_back();
			textures.back().loadFromMemory( new sf::Texture );
			textures.back().get()->loadFromFile( BACKGROUND_TEXTURE );
			textures.back().setUniqueID( static_cast<unique_resource_id_t>( entityID_t::BACKGROUND ) );
		}

		auto bg = std::make_shared<Background>();
		bg->SetType( entityID_t::BACKGROUND );
		auto player = std::make_shared<Player>();
		player->SetType( entityID_t::PLAYER );

		// Initializing player
		{
			playerPointer = player;

			player->SetHealth( MAX_HEALTH );
			player->SetArmor( MAX_ARMOR );

			bool found = false;
			for ( auto& t : textures )
				if ( t.getUniqueID() == static_cast<unique_resource_id_t>( entityID_t::PLAYER ) )
				{
					found = true;
					player->SetTexture( t.get() );
				}

			if ( !found )
				cgf::Logger::log( "Cannot find PLAYER texture!", cgf::Logger::ERROR );

			player->SetPosition( { static_cast<float>( WINDOW_SIZE.x / 2 ), static_cast<float>( WINDOW_SIZE.y / 2 ) } );
			player->SetMovementKeys( movementKeys_t( sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space ) );
			player->SetMovementForces( movementForces_t( -250.f, 250.f, -500.f ) );
		}

		// Initializing bg
		{
			bool found = false;
			for ( auto& t : textures )
				if ( t.getUniqueID() == static_cast<unique_resource_id_t>( entityID_t::BACKGROUND ) )
				{
					found = true;
					bg->SetTexture( t.get() );
				}

			if ( !found )
				cgf::Logger::log( "Cannot find BACKGROUND texture!", cgf::Logger::ERROR );
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

		entities.push_back( bg );
		entities.push_back( player );
		entities.push_back( borderWallDown );
		entities.push_back( borderWallRight );
		entities.push_back( borderWallLeft );
		entities.push_back( borderPlatformLeft );
		entities.push_back( borderPlatformMiddle );
		entities.push_back( borderPlatformRight );

		physicsChecker.AddBoxCollider( player );
		physicsChecker.AddBoxCollider( borderWallDown );
		physicsChecker.AddBoxCollider( borderWallRight );
		physicsChecker.AddBoxCollider( borderWallLeft );
		physicsChecker.AddBoxCollider( borderPlatformLeft );
		physicsChecker.AddBoxCollider( borderPlatformMiddle );
		physicsChecker.AddBoxCollider( borderPlatformRight );

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

		while ( !end )
		{
			if ( !windowPtr->hasFocus() )
				continue;

			while ( windowPtr->pollEvent( event ) )
			{
				if ( event.type == sf::Event::Closed )
					return state_t::EXIT;

				if ( event.type == sf::Event::KeyReleased )
					if ( event.key.code == sf::Keyboard::Escape )
						end = true;
			}

			for ( auto& e : entities )
				e->Update( 1.f / FPS_LIMIT );

			removeUnusedEntities();

			updateUI();

			playerPointer->CheckEvents();
			physicsChecker.Update( 1.f / FPS_LIMIT );

			windowPtr->clear( sf::Color( 100, 100, 100 ) );

			for ( auto& e : entities )
				e->Draw( *windowPtr );

			windowPtr->draw( healthText[0] );
			windowPtr->draw( healthText[1] );
			windowPtr->draw( healthText[2] );
			windowPtr->draw( armorText );
			windowPtr->draw( baseHealthText );


			windowPtr->display();
		}

		// Change in future to ::MENU
		return state_t::EXIT;
	}

	void PlayState::updateThread( seconds_t dt, window_t& w )
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

		cgf::Logger::log( "Thread update...", cgf::Logger::INFO, cgf::Logger::CONSOLE );
	}
}