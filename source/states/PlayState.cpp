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

		MissileManager::Initialize( &this->collisionChecker, &this->entityManager );

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
				text->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::UI_GAME ) );
		}
		// Initializing texts fonts
		{
			// if there is font
			if ( ResourceHolder::fonts.size() )
			{
				for ( auto text : ResourceHolder::texts )
					text->setFont( *ResourceHolder::GetFont( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) ).lock() );
			}
		}
		// Initializing texts sizes and temporary text
		{
			for ( auto text : ResourceHolder::texts )
			{
				text->setCharacterSize( static_cast<uint32_t>( 6 * kd::settings_t::GetInstance().GAMEPLAY.SCALE ) );
				text->setString( "0" );
			}
		}

		// Loading textures
		{
			ResourceHolder::textures.push_back( std::make_shared<textureResource_t>() );

			if ( !ResourceHolder::textures.back()->loadFromFile( kd::settings_t::GetInstance().RESOURCES_PATHES.PLAYER_TEXTURE ) )
			{
				ResourceHolder::textures.pop_back();
				cgf::Logger::Log( "Cannot load texture from path \"" + std::string( kd::settings_t::GetInstance().RESOURCES_PATHES.PLAYER_TEXTURE ) + "\"", cgf::Logger::ERROR );
			} else
			{
				ResourceHolder::textures.back()->SetResourceID( static_cast<uint8_t>( textureResourceID_t::PLAYER ) );
				ResourceHolder::textures.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::ENTITIES ) );
			}

			ResourceHolder::textures.push_back( std::make_shared<textureResource_t>() );
			if ( !ResourceHolder::textures.back()->loadFromFile( kd::settings_t::GetInstance().RESOURCES_PATHES.ENEMY_TEXTURE ) )
			{
				ResourceHolder::textures.pop_back();
				cgf::Logger::Log( "Cannot load texture from path \"" + std::string( kd::settings_t::GetInstance().RESOURCES_PATHES.ENEMY_TEXTURE ) + "\"", cgf::Logger::ERROR );
			} else
			{
				ResourceHolder::textures.back()->SetResourceID( static_cast<uint8_t>( textureResourceID_t::ENEMY ) );
				ResourceHolder::textures.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::ENTITIES ) );
			}
		}


		auto player = this->entityManager.AddEntity<Player>();
		player->SetType( entityID_t::PLAYER );
		player->SetDrawLayer( 1 );
		// Initializing player
		{
			this->playerPointer = player;

			player->SetHealth( kd::settings_t::GetInstance().GAMEPLAY.MAX_HEALTH );
			player->SetArmor( kd::settings_t::GetInstance().GAMEPLAY.MAX_ARMOR );

			player->SetTexture( ResourceHolder::GetTexture( static_cast<uint8_t>( textureResourceID_t::PLAYER ) ) );

			player->SetMovementKeys( movementKeys_t( sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space ) );
			player->SetMovementForces( movementForces_t( -250.0f, 250.0f, -500.0f ) );

			player->AddPowerUp<ImmortalityPowerUp>();
		}

		this->collisionChecker.AddBoxCollider( player );

		// Change it to menu values (some menu before playing etc) in future
		this->level.Load( "data/TestLevel.lvl" );
		this->level.AddEntities( this->entityManager, &this->collisionChecker );
		this->level.InitializeTextures();
		this->level.SetPlayer( this->playerPointer.lock() );

		this->playerView.reset( sf::FloatRect( { 0,0 }, (sf::Vector2f)this->windowPtr->getSize() ) );
		this->playerView.setViewport( sf::FloatRect( 0, 0, 1.0f, 1.0f ) );
		this->updateUIposition();
		this->setLevelBackgroundAsCenterOfView();

		this->EndThread();
	}

	void PlayState::OnStop()
	{
		this->StartThread();

		this->level.RemoveEntities();
		this->entityManager.Clear();
		MissileManager::Shutdown();
		ResourceHolder::DeleteAllResourcesByPriority( static_cast<uint8_t>( resourcePriorites_t::ENTITIES ) );
		ResourceHolder::DeleteAllResourcesByPriority( static_cast<uint8_t>( resourcePriorites_t::LEVEL ) );
		ResourceHolder::DeleteAllResourcesByPriority( static_cast<uint8_t>( resourcePriorites_t::UI_GAME ) );

		this->windowPtr->setView( this->windowPtr->getDefaultView() );

		this->EndThread();
	}

	int16_t PlayState::Run()
	{
		sf::Event event;

		while ( !this->exit )
		{
			state_t stateToSwitch = this->processEvents( event );

			if ( stateToSwitch != state_t::NONE )
			{
				return static_cast<int16_t>( stateToSwitch );
			}

			this->update( 1.0f / kd::settings_t::GetInstance().GLOBAL.FPS_LIMIT );

			this->draw();
		}

		return static_cast<int16_t>( state_t::MENU );
	}

	void PlayState::UpdateThread( seconds_t dt, window_t& w )
	{
		static sf::RectangleShape rectangle;
		rectangle.setFillColor( sf::Color::Transparent );
		rectangle.setOutlineColor( { 125, 125, 125 } );
		rectangle.setOutlineThickness( 5.0f );
		rectangle.setPosition( static_cast<float>( kd::settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * kd::settings_t::GetInstance().GAMEPLAY.SCALE / 2 ), static_cast<float>( kd::settings_t::GetInstance().GLOBAL.WINDOW_SIZE_Y * kd::settings_t::GetInstance().GAMEPLAY.SCALE / 2 ) );
		rectangle.setSize( sf::Vector2f( static_cast<float>( kd::settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X / 2 ), static_cast<float>( kd::settings_t::GetInstance().GLOBAL.WINDOW_SIZE_Y / 2 ) ) );
		rectangle.setOrigin( rectangle.getSize().x / 2, rectangle.getSize().y / 2 );

		rectangle.rotate( 90 * dt );
		static uint32_t i = 1;

		rectangle.setScale( std::fabs( std::sinf( i * 3.14f / 180.0f ) ), std::fabs( std::sinf( i * 3.14f / 180.0f ) ) );
		i++;

		w.clear( sf::Color( 100, 100, 100 ) );
		w.draw( rectangle );
		w.display();

		// It cause some threading issues - messages are overleaping 
		//cgf::Logger::Log( "Thread update...", cgf::Logger::INFO, cgf::Logger::CONSOLE );
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

	state_t PlayState::processEvents( sf::Event& ev )
	{
		while ( this->windowPtr->pollEvent( ev ) )
		{
			if ( ev.type == sf::Event::Closed )
				return state_t::EXIT;

			if ( ev.type == sf::Event::KeyReleased )
				if ( ev.key.code == sf::Keyboard::Escape )
					this->exit = true;

			if ( ev.type == sf::Event::Resized )
			{
				this->playerView.setSize( ev.size.width, ev.size.height );
				this->setLevelBackgroundAsCenterOfView();
			}
		}

		return state_t::NONE;
	}

	void PlayState::update( seconds_t dt )
	{
		this->entityManager.Update( dt );

		this->collisionChecker.Update( 1.0f / kd::settings_t::GetInstance().GLOBAL.FPS_LIMIT );

		this->updateUI();

		MissileManager::Update( 1.0f / kd::settings_t::GetInstance().GLOBAL.FPS_LIMIT );
	}

	void PlayState::draw()
	{
		this->windowPtr->clear( sf::Color( 100, 100, 100 ) );

		this->windowPtr->setView( this->playerView );

		this->entityManager.Draw( *this->windowPtr );
		
		this->windowPtr->setView( this->windowPtr->getDefaultView() );
		for ( auto text : ResourceHolder::texts )
			this->windowPtr->draw( *text );

		this->windowPtr->display();
	}

	void PlayState::updateUIposition()
	{
		for ( auto text : ResourceHolder::texts )
		{
			if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::HP_1 ) )
				text->setPosition(
					98 * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * settings_t::GetInstance().GAMEPLAY.SCALE / 100,
					0
				);
			else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::HP_2 ) )
				text->setPosition(
					98 * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * settings_t::GetInstance().GAMEPLAY.SCALE / 100,
					text->getGlobalBounds().height * 1.5f
				);
			else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::HP_3 ) )
				text->setPosition(
					98 * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * settings_t::GetInstance().GAMEPLAY.SCALE / 100,
					text->getGlobalBounds().height * 1.5f * 2
				);
			else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::ARMOR ) )
				text->setPosition(
					0.5f * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * settings_t::GetInstance().GAMEPLAY.SCALE / 100,
					90 * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_Y * settings_t::GetInstance().GAMEPLAY.SCALE / 100
				);
			else if ( text->GetResourceID() == static_cast<uint8_t>( uiTextResourceID_t::BASE_HP ) )
				text->setPosition(
					98 * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * settings_t::GetInstance().GAMEPLAY.SCALE / 100,
					90 * settings_t::GetInstance().GLOBAL.WINDOW_SIZE_Y * settings_t::GetInstance().GAMEPLAY.SCALE / 100
				);
		}
	}

	void PlayState::setLevelBackgroundAsCenterOfView()
	{
		for ( auto e : this->entityManager.GetEntities() )
			if ( e->GetType() == entityID_t::BACKGROUND )
				this->playerView.setCenter( e->GetPosition().x + this->playerView.getSize().x / 2, e->GetPosition().y + this->playerView.getSize().y / 2 );
	}
}