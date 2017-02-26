/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "CollisionSolver.hpp"

namespace kd
{
	void CollisionSolver::EntityEntity( std::shared_ptr<BoxCollider> colliderA, std::shared_ptr<BoxCollider> colliderB, collisionSide_t colliderAcollisionSide )
	{
		if ( colliderAcollisionSide == None )
		{
			cgf::Logger::log( "Collision solver have wrong collision side info - possible error!", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
			return;
		}

		auto& rectA = colliderA->rectangle;
		auto& rectB = colliderB->rectangle;

		if ( colliderAcollisionSide == Left )
		{
			rectA.left = rectB.left - rectA.width;
			colliderA->velocity.x = 0;
		} else if ( colliderAcollisionSide == Right )
		{
			rectA.left = rectB.left + rectB.width;
			colliderA->velocity.x = 0;
		} else if ( colliderAcollisionSide == Down )
		{
			rectA.top = rectB.top - rectA.height;
			colliderA->velocity.y = 0;
			colliderA->grounded = true;
		} else if ( colliderAcollisionSide == Top )
		{
			rectA.top = rectB.top + rectB.height;
			colliderA->velocity.y = 0;
		}
	}
}