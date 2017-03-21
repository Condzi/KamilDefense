/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <framework/Logger.hpp>

#include "entities/BoxCollider.hpp"
#include "entities/Entity.hpp"
#include "entities/Enemy.hpp"
#include "entities/Player.hpp"
#include "entities/PlayerBase.hpp"

namespace kd
{
	class CollisionSolver final
	{
	public:
		CollisionSolver() = delete;

		static void EntityEntity( std::weak_ptr<BoxCollider> colliderA, std::weak_ptr<BoxCollider> colliderB, collisionSide_t colliderAcollisionSide );
		static void EnemyEntity( std::weak_ptr<BoxCollider> enemyCollider, std::weak_ptr<BoxCollider> colliderB, collisionSide_t enemyCollisionSide );
		static void EnemyPlayer( std::weak_ptr<BoxCollider> enemyCollider, std::weak_ptr<BoxCollider> colliderB, collisionSide_t enemyCollisionSide );
		static void MissileEntity( std::weak_ptr<BoxCollider> bulletCollider );
		static void MissileEnemy( std::weak_ptr<BoxCollider> bulletCollider, std::weak_ptr<BoxCollider> colliderB );
		static void MissilePlayer( std::weak_ptr<BoxCollider> bulletCollider, std::weak_ptr<BoxCollider> colliderB );
		static void MissileMissile( std::weak_ptr<BoxCollider> bulletColliderA, std::weak_ptr<BoxCollider> bulletColliderB );
		static void EnemyBase( std::weak_ptr<BoxCollider> enemy, std::weak_ptr<BoxCollider> base );
	};
}

