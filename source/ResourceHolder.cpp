/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "ResourceHolder.hpp"

namespace kd
{
	std::vector<std::shared_ptr<textureResource_t>> ResourceHolder::textures;
	std::vector<std::shared_ptr<textResource_t>> ResourceHolder::texts;
	std::vector<std::shared_ptr<fontResource_t>> ResourceHolder::fonts;


	void ResourceHolder::Initialize()
	{
		cgf::Logger::Log( "Resource Holder initialized!" );
	}

	void ResourceHolder::Shutdown()
	{
		ResourceHolder::DeleteAllResources();
		cgf::Logger::Log( "Resource Holder shutdown!" );
	}

	void ResourceHolder::DeleteAllResources()
	{
		cgf::Logger::Log( "Starting to delete all resources..." );
		cgf::Logger::Log( std::to_string( ResourceHolder::textures.size() ) + " Textures" );
		ResourceHolder::textures.clear();
		cgf::Logger::Log( std::to_string( ResourceHolder::texts.size() ) + " Texts" );
		ResourceHolder::texts.clear();
		cgf::Logger::Log( std::to_string( ResourceHolder::fonts.size() ) + " Fonts" );
		ResourceHolder::fonts.clear();
		cgf::Logger::Log( "All resources deleted!" );
	}

	void ResourceHolder::DeleteAllResourcesByPriority( uint8_t priority )
	{
		cgf::Logger::Log( "Starting to delete all resources of priority " + std::to_string( priority ) );

		for ( auto textureIterator = ResourceHolder::textures.begin(); textureIterator != ResourceHolder::textures.end(); )
		{
			if ( ( *textureIterator )->GetResourcePriority() == priority )
				textureIterator = ResourceHolder::textures.erase( textureIterator );
			else
				textureIterator++;
		}
		for ( auto textsIterator = ResourceHolder::texts.begin(); textsIterator != ResourceHolder::texts.end(); )
		{
			if ( ( *textsIterator )->GetResourcePriority() == priority )
				textsIterator = ResourceHolder::texts.erase( textsIterator );
			else
				textsIterator++;
		}
		for ( auto fontIterator = ResourceHolder::fonts.begin(); fontIterator != ResourceHolder::fonts.end(); )
		{
			if ( ( *fontIterator )->GetResourcePriority() == priority )
				fontIterator = ResourceHolder::fonts.erase( fontIterator );
			else
				fontIterator++;
		}

		cgf::Logger::Log( "All resources of priority " + std::to_string( priority ) + " deleted" );
	}

	void ResourceHolder::DeleteAllResourcesByID( uint8_t id )
	{
		cgf::Logger::Log( "Starting to delete all resources of ID " + std::to_string( id ) );

		for ( auto textureIterator = ResourceHolder::textures.begin(); textureIterator != ResourceHolder::textures.end(); )
		{
			if ( ( *textureIterator )->GetResourceID() == id )
				textureIterator = ResourceHolder::textures.erase( textureIterator );
			else
				textureIterator++;
		}
		for ( auto textsIterator = ResourceHolder::texts.begin(); textsIterator != ResourceHolder::texts.end(); )
		{
			if ( ( *textsIterator )->GetResourceID() == id )
				textsIterator = ResourceHolder::texts.erase( textsIterator );
			else
				textsIterator++;
		}
		for ( auto fontIterator = ResourceHolder::fonts.begin(); fontIterator != ResourceHolder::fonts.end(); )
		{
			if ( ( *fontIterator )->GetResourceID() == id )
				fontIterator = ResourceHolder::fonts.erase( fontIterator );
			else
				fontIterator++;
		}

		cgf::Logger::Log( "All resources of ID " + std::to_string( id ) + " deleted" );
	}

	std::weak_ptr<textureResource_t> ResourceHolder::GetTexture( uint8_t id )
	{
		for ( auto ptr : ResourceHolder::textures )
			if ( ptr->GetResourceID() == id )
				return ptr;

		cgf::Logger::Log( "Cannot find Texture of ID " + std::to_string( id ), cgf::Logger::ERROR );
		return std::weak_ptr<textureResource_t>();
	}

	std::weak_ptr<textResource_t> ResourceHolder::GetText( uint8_t id )
	{
		for ( auto ptr : ResourceHolder::texts )
			if ( ptr->GetResourceID() == id )
				return ptr;

		cgf::Logger::Log( "Cannot find Text of ID " + std::to_string( id ), cgf::Logger::ERROR );
		return std::weak_ptr<textResource_t>();
	}

	std::weak_ptr<fontResource_t> ResourceHolder::GetFont( uint8_t id )
	{
		for ( auto ptr : ResourceHolder::fonts )
			if ( ptr->GetResourceID() == id )
				return ptr;

		cgf::Logger::Log( "Cannot find Font of ID " + std::to_string( id ), cgf::Logger::ERROR );
		return std::weak_ptr<fontResource_t>();
	}
}