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
			cgf::Logger::Log( "Collision solver have wrong collision side info - possible error!", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
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

	void CollisionSolver::EnemyEntity( std::shared_ptr<BoxCollider> enemyCollider, std::shared_ptr<BoxCollider> colliderB, collisionSide_t enemyCollisionSide )
	{
		if ( enemyCollisionSide == None )
		{
			cgf::Logger::Log( "Collision solver have wrong collision side info - possible error!", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
			return;
		}

		auto& rectA = enemyCollider->rectangle;
		auto& rectB = colliderB->rectangle;

		if ( enemyCollisionSide == Left )
		{
			rectA.left = rectB.left - rectA.width;
			enemyCollider->velocity.x = -enemyCollider->velocity.x;
		} else if ( enemyCollisionSide == Right )
		{
			rectA.left = rectB.left + rectB.width;
			enemyCollider->velocity.x = -enemyCollider->velocity.x;
		} else if ( enemyCollisionSide == Down )
		{
			rectA.top = rectB.top - rectA.height;
			enemyCollider->velocity.y = 0;
		} else if ( enemyCollisionSide == Top )
		{
			rectA.top = rectB.top + rectB.height;
			enemyCollider->velocity.y = 0;
		}
	}

	void CollisionSolver::EnemyPlayer( std::shared_ptr<BoxCollider> enemyCollider, std::shared_ptr<BoxCollider> playerCollider, collisionSide_t enemyCollisionSide )
	{
		Enemy* enemyPtr = dynamic_cast<Enemy*>( enemyCollider->parentPointer );
		Player* playerPtr = dynamic_cast<Player*>( playerCollider->parentPointer );

		enemyPtr->AddDamage( 10 );
		playerPtr->AddDamage( 20 );
	}
}