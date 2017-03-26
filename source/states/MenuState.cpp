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
			if ( !ResourceHolder::fonts.back()->loadFromFile( SETTINGS.RESOURCES_PATHES.FONT ) )
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

		auto buttonStart = std::make_shared<Button>();
		{
			buttonStart->SetDrawLayer( 1 );
			buttonStart->SetPosition( { SETTINGS.GLOBAL.WINDOW_SIZE_X / 2.0f, SETTINGS.GLOBAL.WINDOW_SIZE_Y / 2.0f } );
			buttonStart->SetType( entityID_t::BUTTON_START );
			buttonStart->SetTextFont( ResourceHolder::GetFont( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) ) );
			buttonStart->SetTextString( "START" );
			buttonStart->SetShapeSize( { 64, 16 } );
			buttonStart->SetTextSize( 33 );
			buttonStart->SetOutline( 1 * SETTINGS.GAMEPLAY.SCALE, sf::Color::Blue, sf::Color::Transparent );
		}

		auto buttonExit = std::make_shared<Button>();
		{
			buttonExit->SetDrawLayer( 1 );
			buttonExit->SetPosition( { SETTINGS.GLOBAL.WINDOW_SIZE_X / 2.0f, SETTINGS.GLOBAL.WINDOW_SIZE_Y / 2.0f + 32 } );
			buttonExit->SetType( entityID_t::BUTTON_EXIT );
			buttonExit->SetTextFont( ResourceHolder::GetFont( static_cast<uint8_t>( fontResourceID_t::UI_FONT ) ) );
			buttonExit->SetTextString( "EXIT" );
			buttonExit->SetShapeSize( { 64, 16 } );
			buttonExit->SetTextSize( 33 );
			buttonExit->SetOutline( 1 * SETTINGS.GAMEPLAY.SCALE, sf::Color::Blue, sf::Color::Transparent );
		}

		auto bg = std::make_shared<Background>();
		bg->SetType( entityID_t::BACKGROUND );
		bg->SetDrawLayer( 0 );
		bg->SetTexture( ResourceHolder::GetTexture( static_cast<uint8_t>( textureResourceID_t::MENU_BG ) ) );
		bg->SetSpriteScale( { 2 * SETTINGS.GAMEPLAY.SCALE, 2 * SETTINGS.GAMEPLAY.SCALE } );
		this->entities.push_back( bg );

		this->entities.push_back( buttonStart );
		this->entities.push_back( buttonExit );
	}

	void MenuState::OnStop()
	{
		entities.clear();
		drawables.clear();
		ResourceHolder::DeleteAllResourcesByPriority( static_cast<uint8_t>( resourcePriorites_t::UI_MENU ) );
	}

	int16_t MenuState::Run()
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

			this->update( 1.0f / SETTINGS.GLOBAL.FPS_LIMIT );

			this->draw();
		}

		return static_cast<int16_t>( state_t::EXIT );
	}
	void MenuState::removeUnusedEntities()
	{
		for ( auto it = this->entities.begin(); it != this->entities.end();)
		{
			if ( ( *it )->IsWishingDelete() )
				it = this->entities.erase( it );
			else
				it++;
		}
	}

	void MenuState::updateDrawables()
	{
		this->drawables.clear();

		for ( auto entity : this->entities )
		{
			auto casted = std::dynamic_pointer_cast<Drawable>( entity );
			if ( casted )
				this->drawables.push_back( casted );
		}
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
					auto mouseCoords = sf::Mouse::getPosition( *this->windowPtr );

					for ( auto e : this->entities )
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
		}

		return state_t::NONE;
	}

	void MenuState::update( seconds_t dt )
	{
		for ( size_t i = 0; i < this->entities.size(); i++ )
			this->entities[i]->Update( dt );

		this->updateDrawables();
	}

	void MenuState::draw()
	{
		this->windowPtr->clear();

		auto drawLayersInterval = this->getDrawLayersInterval();

		size_t entitiesAlreadyDrawn = 0;
		for ( int8_t currentLayer = drawLayersInterval.first; ( currentLayer < drawLayersInterval.second + 1 && entitiesAlreadyDrawn < this->drawables.size() ); currentLayer++ )
			for ( auto drawable : this->drawables )
				if ( drawable.lock()->GetDrawLayer() == currentLayer )
				{
					drawable.lock()->Draw( *this->windowPtr );
					entitiesAlreadyDrawn++;
				}

		for ( auto text : ResourceHolder::texts )
			this->windowPtr->draw( *text );

		this->windowPtr->display();
	}

	std::pair<int8_t, int8_t> MenuState::getDrawLayersInterval()
	{
		int8_t min = INT8_MAX, max = INT8_MIN;
		int8_t currentLayer = 0;

		for ( auto drawable : this->drawables )
		{
			currentLayer = drawable.lock()->GetDrawLayer();

			if ( currentLayer > max ) max = currentLayer;
			if ( currentLayer < min ) min = currentLayer;
		}

		return std::pair<int8_t, int8_t>( min, max );
	}
}