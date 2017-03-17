/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

namespace kd
{
	template<class Resource>
	class ResourceWrapper final :
		public Resource
	{
	public:
		ResourceWrapper() :
			priority( 0 ),
			resourceID( 0 )
		{}
		ResourceWrapper( const Resource& res ) :
			Resource( res ),
			priority( 0 ),
			resourceID( 0 )
		{}

		uint8_t GetResourcePriority()
		{
			return this->priority;
		}
		uint8_t GetResourceID()
		{
			return this->resourceID;
		}

		void SetResourcePriority( uint8_t val )
		{
			this->priority = val;
		}
		void SetResourceID( uint8_t val )
		{
			this->resourceID = val;
		}

	private:
		uint8_t priority;
		uint8_t resourceID;
	};
}