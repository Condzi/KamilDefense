/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <vector>

#include <Logger.hpp>

#include "Types.hpp"

namespace kd
{
	struct ResourceHolder final
	{
		static std::vector<std::shared_ptr<textureResource_t>> textures;
		static std::vector<std::shared_ptr<textResource_t>> texts;
		static std::vector<std::shared_ptr<fontResource_t>> fonts;

		static void Initialize();
		static void Shutdown();

		static void DeleteAllResources();
		static void DeleteAllResourcesByPriority( uint8_t priority );
		static void DeleteAllResourcesByID( uint8_t id );

		static std::weak_ptr<textureResource_t> GetTexture( uint8_t id );
		static std::weak_ptr<textResource_t> GetText( uint8_t id );
		static std::weak_ptr<fontResource_t> GetFont( uint8_t id );
	};
}