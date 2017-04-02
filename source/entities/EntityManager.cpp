/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "EntityManager.hpp"

namespace kd
{
	void EntityManager::Update( seconds_t dt )
	{
		this->removeUnusedEntities();

		// for( auto ptr : this->entities) loop doesn't work with spawners - it doesn't update size parameter!
		for ( size_t i = 0; i < this->entities.size(); i++ )
			this->entities[i]->Update( dt );

		this->updateDrawables();
	}

	void EntityManager::Draw( sf::RenderTarget& target )
	{
		auto drawLayersInterval = this->getDrawLayersInterval();

		size_t entitiesAlreadyDrawn = 0;
		for ( int8_t currentLayer = drawLayersInterval.first; ( currentLayer < drawLayersInterval.second + 1 && entitiesAlreadyDrawn < this->drawables.size() ); currentLayer++ )
		{
			for ( auto drawable : this->drawables )
				if ( drawable.lock()->GetDrawLayer() == currentLayer )
				{
					drawable.lock()->Draw( target );
					entitiesAlreadyDrawn++;
				}
		}
	}

	void EntityManager::removeUnusedEntities()
	{
		for ( auto it = this->entities.begin(); it != this->entities.end();)
		{
			if ( ( *it )->IsWishingDelete() )
				it = this->entities.erase( it );
			else
				it++;
		}
	}

	void EntityManager::updateDrawables()
	{
		this->drawables.clear();

		for ( auto entity : this->entities )
		{
			auto casted = std::dynamic_pointer_cast<Drawable>( entity );
			// Check if casted succed - if yes, add to vector.
			if ( casted )
				this->drawables.push_back( casted );
		}
	}

	std::pair<int8_t, int8_t> EntityManager::getDrawLayersInterval()
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