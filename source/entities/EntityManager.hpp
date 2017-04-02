/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/
#pragma once

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "Drawable.hpp"

namespace kd
{
	class EntityManager final
	{
	public:
		EntityManager()
		{}

		EntityManager( const EntityManager& ) = delete;
		EntityManager& operator=( const EntityManager& ) = delete;

		const std::vector<std::shared_ptr<Entity>>& GetEntities()
		{
			return this->entities;
		}
		/*
			Adds Entity to vector and returns shared_ptr to it.
		*/
		template<class T>
		typename std::enable_if<std::is_base_of<Entity, T>::value, std::shared_ptr<T>>::type
		AddEntity()
		{
			auto ptr = std::make_shared<T>();
			this->entities.push_back( ptr );

			return ptr;
		}
		/*
			Adds Entity to vector and returns shared_ptr to it.
		*/
		template<class T>
		typename std::enable_if<std::is_base_of<Entity, T>::value, std::shared_ptr<T>>::type
		AddEntity( std::shared_ptr<T> entityToAdd )
		{
			for ( auto e : this->entities )
				if ( e == entityToAdd )
				{
					cgf::Logger::Log( "Cannot add entity to EntityManager - found pointer pointing to same entity", cgf::Logger::ERROR );
					return nullptr;
				}

			this->entities.push_back( entityToAdd );

			return entityToAdd;
		}

		void Clear()
		{
			this->entities.clear();
			this->drawables.clear();
		}

		void Update( seconds_t dt );
		void Draw( sf::RenderTarget& target );

	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::vector<std::weak_ptr<Drawable>> drawables;

		void removeUnusedEntities();
		void updateDrawables();
		std::pair<int8_t, int8_t> getDrawLayersInterval();
	};
}
