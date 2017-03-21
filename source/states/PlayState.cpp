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

		MissileManager::Initialize( &this->collisionChecker, &this->entities );

		// Loading font
		{
			ResourceHolder::fonts.push_back( std::make_shared<fontResource_t>() );
			if ( !ResourceHolder::fonts.back()->loadFromFile( FONT_PATH ) )
			{
				ResourceHolder::fonts.pop_back();
				cgf::Logger::Log( "Cannot load font file!", cgf::Logger::ERROR );
			} else
			{
				ResourceHolder::fonts.back()->SetResourceID( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) );
				ResourceHolder::fonts.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::UI ) );
			}
		}
		// Initializing texts
		{
			ResourceHolder::texts.push_back( std::make_shared<textResource_t>() );
			ResourceHolder::texts.back()->SetResourceID( static_cast<uint8_t>( uiTextResourceID_t::HP_1 ) );
			ResourceHolder::texts.push_back( std::make_shared<textResource_t>() );
			ResourceHolder::texts.back()->SetResourceID( static_cast<uint8_t>( uiTextResourceID_t::HP_2 ) );
			ResourceHolder::texts.push_back( std::make_shared<textResource_t>() );
			ResourceHolder::texts.back()->SetResourceID( static_cast<uint8_t>( uiTextResourceID_t::HP_3 ) );
			ResourceHolder::texts.push_back( std::make_shared<textResource_t>() );
			ResourceHolder::texts.back()->SetResourceID( static_cast<uint8_t>( uiTextResourceID_t::ARMOR ) );
			ResourceHolder::texts.push_back( std::make_shared<textResource_t>() );
			ResourceHolder::texts.back()->SetResourceID( static_cast<uint8_t>( uiTextResourceID_t::BASE_HP ) );

			for ( auto text : ResourceHolder::texts )
				text->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::UI ) );
		}
		// Initializing texts fonts
		{
			// if there is font
			if ( ResourceHolder::fonts.size() )
			{
				for ( auto text : ResourceHolder::texts )
					text->setFont( *ResourceHolder::fonts.back().get() );
			}
		}
		// Initializing texts sizes
		{
			for ( auto text : ResourceHolder::texts )
				text->setCharacterSize( static_cast<uint32_t>( 6 * SCALE ) );
		}
		// Initializing texts posiion
		{
			for ( auto text : ResourceHolder::texts )
			{
				if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::HP_1 ) )
					text->setPosition( 64.5f * SCALE, 0 );
				else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::HP_2 ) )
					text->setPosition( 64.5f * SCALE, 5 * SCALE );
				else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::HP_3 ) )
					text->setPosition( 64.5f * SCALE, 10 * SCALE );
				else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::ARMOR ) )
					text->setPosition( 1 * SCALE, 62 * SCALE );
				else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::BASE_HP ) )
					text->setPosition( 62 * SCALE, 62 * SCALE );
			}
		}

		// Loading textures
		{
			ResourceHolder::textures.push_back( std::make_shared<textureResource_t>() );

			if ( !ResourceHolder::textures.back()->loadFromFile( PLAYER_TEXTURE_PATH ) )
			{
				ResourceHolder::textures.pop_back();
				cgf::Logger::Log( "Cannot load texture from path \"" + std::string( PLAYER_TEXTURE_PATH ) + "\"", cgf::Logger::ERROR );
			} else
			{
				ResourceHolder::textures.back()->SetResourceID( static_cast<uint8_t>( textureResourceID_t::PLAYER ) );
				ResourceHolder::textures.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::ENTITIES ) );
			}

			ResourceHolder::textures.push_back( std::make_shared<textureResource_t>() );
			if ( !ResourceHolder::textures.back()->loadFromFile( ENEMY_TEXTURE_PATH ) )
			{
				ResourceHolder::textures.pop_back();
				cgf::Logger::Log( "Cannot load texture from path \"" + std::string( ENEMY_TEXTURE_PATH ) + "\"", cgf::Logger::ERROR );
			} else
			{
				ResourceHolder::textures.back()->SetResourceID( static_cast<uint8_t>( textureResourceID_t::ENEMY ) );
				ResourceHolder::textures.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::ENTITIES ) );
			}
		}


		auto player = std::make_shared<Player>();
		player->SetType( entityID_t::PLAYER );
		player->SetDrawLayer( 1 );
		// Initializing player
		{
			this->playerPointer = player;

			player->SetHealth( MAX_HEALTH );
			player->SetArmor( MAX_ARMOR );

			player->SetTexture( ResourceHolder::GetTexture( static_cast<uint8_t>( textureResourceID_t::PLAYER ) ) );

			player->SetMovementKeys( movementKeys_t( sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space ) );
			player->SetMovementForces( movementForces_t( -250.0f, 250.0f, -500.0f ) );
		}

		this->entities.push_back( player );
		this->collisionChecker.AddBoxCollider( player );

		this->level.Load( "data/TestLevel.lvl" );
		this->level.AddEntities( &this->entities, &this->collisionChecker );
		this->level.InitializeTextures();
		this->level.SetPlayer( this->playerPointer.lock() );

		this->EndThread();
	}

	void PlayState::OnStop()
	{
		this->StartThread();

		this->level.RemoveEntities();
		this->entities.clear();
		MissileManager::Shutdown();

		this->EndThread();
	}

	int16_t PlayState::Run()
	{
		sf::Event event;

		while ( !this->exit )
		{
			this->removeUnusedEntities();

			state_t stateToSwitch = this->processEvents( event );

			if ( stateToSwitch != state_t::NONE )
			{
				return static_cast<int16_t>( stateToSwitch );
			}

			this->update( 1.0f / FPS_LIMIT );

			this->draw();
		}

		// Change in future to ::MENU
		return static_cast<int16_t>( state_t::EXIT );
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
		auto hp = this->playerPointer.lock()->GetHealth();

		if ( hp >= 100 )
			ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::HP_3 ) ).lock()->setString( sf::String( std::to_string( hp )[2] ) );
		else
			ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::HP_3 ) ).lock()->setString( "-" );

		if ( hp >= 10 )
			ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::HP_2 ) ).lock()->setString( sf::String( std::to_string( hp )[1] ) );
		else
			ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::HP_2 ) ).lock()->setString( "-" );

		ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::HP_1 ) ).lock()->setString( sf::String( std::to_string( hp )[0] ) );

		ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::ARMOR ) ).lock()->setString( std::to_string( playerPointer.lock()->GetArmor() ) );

		ResourceHolder::GetText( static_cast<uint8_t>( uiTextResourceID_t::BASE_HP ) ).lock()->setString( std::to_string( this->playerPointer.lock()->GetBaseHealth() ) );
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

	void PlayState::updateDrawables()
	{
		// temporary?
		this->drawables.clear();

		for ( auto entity : this->entities )
		{
			if ( std::dynamic_pointer_cast<Drawable>( entity ) )
				this->drawables.push_back( std::dynamic_pointer_cast<Drawable>( entity ) );
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

		this->collisionChecker.Update( 1.0f / FPS_LIMIT );

		this->updateUI();

		MissileManager::Update( 1.0f / FPS_LIMIT );

		this->updateDrawables();
	}

	void PlayState::draw()
	{
		this->windowPtr->clear( sf::Color( 100, 100, 100 ) );

		size_t entitiesAlreadyDrawn = 0;
		for ( int8_t currentLayer = -128; ( currentLayer < 127 && entitiesAlreadyDrawn < this->drawables.size() ); currentLayer++ )
		{
			for ( auto drawable : this->drawables )
				if ( drawable.lock()->GetDrawLayer() == currentLayer )
				{
					drawable.lock()->Draw( *this->windowPtr );
					entitiesAlreadyDrawn++;
				}
		}

		for ( auto text : ResourceHolder::texts )
			this->windowPtr->draw( *text );

		this->windowPtr->display();
	}
}