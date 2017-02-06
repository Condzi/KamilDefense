/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <memory>
#include <string>

#include <Config.hpp>

namespace CGF_NAMESPACE
{
	namespace CGF_PRIVATE
	{
		class ResourceBase
		{
		public:
			ResourceBase() : 
				used(false), 
				loaded(false), 
				checkCount(false), 
				id(-1)
			{}

			virtual ~ResourceBase() = default;

			bool isUsed() { return used; }
			bool isLoaded() { return loaded; }
			unique_resource_id_t getUniqueID() { return id; }

			void markUsed() { used = true; }
			void markUnused() { used = false; }
			void setUniqueID(unique_resource_id_t id_) { id = id_; }
			// If there is no reference for resource its automaticly marked as unused
			// Use it if you *have* references to resource; otherwise you must manually mark it as unused
			void setCheckCount(bool val) { checkCount = val; }

			virtual void update(seconds_t dt) = 0;

		protected:
			bool used;
			bool loaded;
			bool checkCount;
			unique_resource_id_t id;
		};
	}

	template<class T>
	class Resource : public CGF_PRIVATE::ResourceBase
	{
	public:
		Resource() : 
			deleteClock(0), 
			resource(nullptr) 
		{}

		virtual ~Resource() = default;

		virtual bool loadFromFile(const std::string& path) { return false; }
		std::shared_ptr<T> loadFromMemory(T* allocated)
		{
			if (!allocated)
				loaded = false;
			else
			{
				resource.reset(allocated);
				loaded = true;
				used = true;
				return resource;
			}
		}

		std::size_t getSize() { return sizeof(resource); }
		std::shared_ptr<T> get() { this->used = true; return resource; }

		void update(seconds_t dt) override
		{
			if(checkCount)
				if (resource.use_count() <= 1)
					used = false;

			if (!loaded || (used && loaded))
				return;

			if (deleteClock + dt > RESOURCE_DELETE_TIME)
			{
				resource.reset();
				deleteClock = 0;

				used = false;
				loaded = false;
				id = -1;
			}
			else
				deleteClock += dt;
		}

	private:
		seconds_t deleteClock;

	protected:
		std::shared_ptr<T> resource;
	};
}