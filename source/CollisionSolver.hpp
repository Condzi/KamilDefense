/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <Logger.hpp>

#include "BoxCollider.hpp"
#include "Entity.hpp"

namespace kd
{
	class CollisionSolver final
	{
	public:
		CollisionSolver() = delete;

		//static void bulletEntity(...);
		static void entityEntity(std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB, collision_side_t colliderAcollisionSide);
	};
}

