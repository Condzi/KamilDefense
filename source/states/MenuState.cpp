/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "MenuState.hpp"

namespace kd
{
	void MenuState::OnStart()
	{
		// Loading font
		if ( !ResourceHolder::fonts.size() )
		{
			ResourceHolder::fonts.push_back( std::make_shared<fontResource_t>() );
			if ( !ResourceHolder::fonts.back()->loadFromFile( kd::settings_t::GetInstance().RESOURCES_PATHES.FONT ) )
			{
				ResourceHolder::fonts.pop_back();
				cgf::Logger::Log( "Cannot load font file!", cgf::Logger::ERROR );
			} else
			{
				ResourceHolder::fonts.back()->SetResourceID( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) );
				ResourceHolder::fonts.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::UI_GAME ) );
			}
		}

		// Loading bg
		ResourceHolder::textures.push_back( std::make_shared<textureResource_t>() );
		if ( !ResourceHolder::textures.back()->loadFromFile( "data/textures/menuBG.png" ) )
		{
			ResourceHolder::textures.pop_back();
			cgf::Logger::Log( "Cannot load Menu Background Texture!", cgf::Logger::ERROR );
		} else
		{
			ResourceHolder::textures.back()->SetResourceID( static_cast<uint8_t>( textureResourceID_t::MENU_BG ) );
			ResourceHolder::textures.back()->SetResourcePriority( static_cast<uint8_t>( resourcePriorites_t::UI_MENU ) );
		}

		auto buttonStart = entityManager.AddEntity<Button>();
		{
			buttonStart->SetDrawLayer( 1 );
			buttonStart->SetPosition( { 50 * this->windowPtr->getSize().x / 100.0f, 50 * this->windowPtr->getSize().y / 100.0f } );
			buttonStart->SetType( entityID_t::BUTTON_START );
			buttonStart->SetTextFont( ResourceHolder::GetFont( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) ) );
			buttonStart->SetTextString( "START" );
			buttonStart->SetShapeSize( { 128, 32 } );
			buttonStart->SetTextSize( 66 );
			buttonStart->SetOutline( 1 * kd::settings_t::GetInstance().GAMEPLAY.SCALE, sf::Color::Transparent, sf::Color::Transparent );
		}

		auto buttonExit = entityManager.AddEntity<Button>();
		{
			buttonExit->SetDrawLayer( 1 );
			buttonExit->SetPosition( { 50 * this->windowPtr->getSize().x / 100.0f, 56 * this->windowPtr->getSize().y / 100.0f } );
			buttonExit->SetType( entityID_t::BUTTON_EXIT );
			buttonExit->SetTextFont( ResourceHolder::GetFont( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) ) );
			buttonExit->SetTextString( "EXIT" );
			buttonExit->SetShapeSize( { 128, 32 } );
			buttonExit->SetTextSize( 66 );
			buttonExit->SetOutline( 1 * kd::settings_t::GetInstance().GAMEPLAY.SCALE, sf::Color::Transparent, sf::Color::Transparent );
		}

		auto bg = entityManager.AddEntity<Background>();
		bg->SetType( entityID_t::BACKGROUND );
		bg->SetDrawLayer( 0 );
		bg->SetTexture( ResourceHolder::GetTexture( static_cast<uint8_t>( textureResourceID_t::MENU_BG ) ) );
		bg->SetSpriteScale( {
			kd::settings_t::GetInstance().GLOBAL.WINDOW_SIZE_X * kd::settings_t::GetInstance().GAMEPLAY.SCALE / bg->GetSprite().getGlobalBounds().width,
			kd::settings_t::GetInstance().GLOBAL.WINDOW_SIZE_Y * kd::settings_t::GetInstance().GAMEPLAY.SCALE / bg->GetSprite().getGlobalBounds().height
		} );

		this->view.reset( sf::FloatRect( { 0,0 }, ( sf::Vector2f )this->windowPtr->getSize() ) );
		this->view.setViewport( sf::FloatRect( 0, 0, 1.0f, 1.0f ) );

		// Getting first up-left pixel as clear color
		this->clearColor = ResourceHolder::GetTexture( static_cast<uint8_t>( textureResourceID_t::MENU_BG ) ).lock()->copyToImage().getPixel( 1, 1 );
	}

	void MenuState::OnStop()
	{
		this->windowPtr->setView( this->windowPtr->getDefaultView() );
		this->entityManager.Clear();
		ResourceHolder::DeleteAllResourcesByPriority( static_cast<uint8_t>( resourcePriorites_t::UI_MENU ) );
	}

	int16_t MenuState::Run()
	{
		sf::Event event;

		while ( !this->exit )
		{
			state_t stateToSwitch = this->processEvents( event );

			if ( stateToSwitch != state_t::NONE )
			{
				return static_cast<int16_t>( stateToSwitch );
			}

			this->entityManager.Update( 1.0f / kd::settings_t::GetInstance().GLOBAL.FPS_LIMIT );

			this->draw();
		}

		return static_cast<int16_t>( state_t::EXIT );
	}

	state_t MenuState::processEvents( sf::Event& ev )
	{
		while ( this->windowPtr->pollEvent( ev ) )
		{
			if ( ev.type == sf::Event::Closed )
				return state_t::EXIT;

			if ( ev.type == sf::Event::KeyReleased )
			{
				if ( ev.key.code == sf::Keyboard::Escape )
					this->exit = true;
			}

			if ( ev.type == sf::Event::MouseButtonReleased )
			{
				if ( ev.key.code == sf::Mouse::Left )
				{
					auto mouseCoords = this->windowPtr->mapPixelToCoords( sf::Mouse::getPosition( *this->windowPtr ) );

					for ( auto e : this->entityManager.GetEntities() )
					{
						if ( e->GetType() == entityID_t::BUTTON_START )
							if ( std::dynamic_pointer_cast<Button>( e )->GetRectangle().contains( ( sf::Vector2f )mouseCoords ) )
								return state_t::PLAY;

						if ( e->GetType() == entityID_t::BUTTON_EXIT )
							if ( std::dynamic_pointer_cast<Button>( e )->GetRectangle().contains( ( sf::Vector2f )mouseCoords ) )
								return state_t::EXIT;
					}
				}
			}

			if ( ev.type == sf::Event::Resized )
				this->view.setSize( ev.size.width, ev.size.height );
		}

		return state_t::NONE;
	}

	void MenuState::draw()
	{
		this->windowPtr->clear( this->clearColor );

		this->windowPtr->setView( this->view );
		this->entityManager.Draw( *this->windowPtr );

		for ( auto text : ResourceHolder::texts )
			this->windowPtr->draw( *text );

		this->windowPtr->display();
	}
}