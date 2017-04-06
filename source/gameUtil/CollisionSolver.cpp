/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "CollisionSolver.hpp"

namespace kd
{
	void CollisionSolver::EntityEntity( std::weak_ptr<BoxCollider> colliderA, std::weak_ptr<BoxCollider> colliderB, collisionSide_t colliderAcollisionSide )
	{
		if ( colliderAcollisionSide == collisionSide_t::NONE )
		{
			cgf::Logger::Log( "Collision solver have wrong collision side info - possible error!", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
			return;
		}

		auto& rectA = colliderA.lock()->rectangle;
		auto& rectB = colliderB.lock()->rectangle;

		if ( colliderAcollisionSide == collisionSide_t::LEFT )
		{
			rectA.left = rectB.left - rectA.width;
			colliderA.lock()->velocity.x = 0;
		} else if ( colliderAcollisionSide == collisionSide_t::RIGHT )
		{
			rectA.left = rectB.left + rectB.width;
			colliderA.lock()->velocity.x = 0;
		} else if ( colliderAcollisionSide == collisionSide_t::DOWN )
		{
			rectA.top = rectB.top - rectA.height;
			colliderA.lock()->velocity.y = 0;
			colliderA.lock()->grounded = true;
		} else if ( colliderAcollisionSide == collisionSide_t::TOP )
		{
			rectA.top = rectB.top + rectB.height;
			colliderA.lock()->velocity.y = 0;
		}
	}

	void CollisionSolver::EnemyEntity( std::weak_ptr<BoxCollider> enemyCollider, std::weak_ptr<BoxCollider> colliderB, collisionSide_t enemyCollisionSide )
	{
		if ( enemyCollisionSide == collisionSide_t::NONE )
		{
			cgf::Logger::Log( "Collision solver have wrong collision side info - possible error!", cgf::Logger::WARNING, cgf::Logger::CONSOLE );
			return;
		}

		auto& rectA = enemyCollider.lock()->rectangle;
		auto& rectB = colliderB.lock()->rectangle;

		if ( enemyCollisionSide == collisionSide_t::LEFT )
		{
			rectA.left = rectB.left - rectA.width;
			enemyCollider.lock()->velocity.x = -enemyCollider.lock()->velocity.x;
		} else if ( enemyCollisionSide == collisionSide_t::RIGHT )
		{
			rectA.left = rectB.left + rectB.width;
			enemyCollider.lock()->velocity.x = -enemyCollider.lock()->velocity.x;
		} else if ( enemyCollisionSide == collisionSide_t::DOWN )
		{
			rectA.top = rectB.top - rectA.height;
			enemyCollider.lock()->velocity.y = 0;
		} else if ( enemyCollisionSide == collisionSide_t::TOP )
		{
			rectA.top = rectB.top + rectB.height;
			enemyCollider.lock()->velocity.y = 0;
		}
	}

	void CollisionSolver::EnemyPlayer( std::weak_ptr<BoxCollider> enemyCollider, std::weak_ptr<BoxCollider> playerCollider, collisionSide_t enemyCollisionSide )
	{
		Enemy* enemyPtr = dynamic_cast<Enemy*>( enemyCollider.lock()->parentPointer );
		Player* playerPtr = dynamic_cast<Player*>( playerCollider.lock()->parentPointer );

		enemyPtr->AddDamage( 10 );
		playerPtr->AddDamage( 20 );
	}

	void CollisionSolver::MissileEntity( std::weak_ptr<BoxCollider> bulletCollider )
	{
		bulletCollider.lock()->parentPointer->SetWishDelete( true );
	}

	void CollisionSolver::MissileEnemy( std::weak_ptr<BoxCollider> bulletCollider, std::weak_ptr<BoxCollider> colliderB )
	{
		if ( bulletCollider.lock()->parentPointer->GetType() == entityID_t::BULLET_PLAYER )
		{
			dynamic_cast<Enemy*>( colliderB.lock()->parentPointer )->AddDamage( kd::settings_t::GetInstance().GAMEPLAY.MAX_HEALTH / 10 );
			bulletCollider.lock()->parentPointer->SetWishDelete( true );
		}
	}

	void CollisionSolver::MissilePlayer( std::weak_ptr<BoxCollider> bulletCollider, std::weak_ptr<BoxCollider> colliderB )
	{
		if ( bulletCollider.lock()->parentPointer->GetType() == entityID_t::BULLET_ENEMY )
		{
			dynamic_cast<Player*>( colliderB.lock()->parentPointer )->AddDamage( kd::settings_t::GetInstance().GAMEPLAY.MAX_HEALTH / 12 );
			bulletCollider.lock()->parentPointer->SetWishDelete( true );
		}
	}

	void CollisionSolver::MissileMissile( std::weak_ptr<BoxCollider> bulletColliderA, std::weak_ptr<BoxCollider> bulletColliderB )
	{
		bulletColliderA.lock()->parentPointer->SetWishDelete( true );
		bulletColliderB.lock()->parentPointer->SetWishDelete( true );
	}

	void CollisionSolver::EnemyBase( std::weak_ptr<BoxCollider> enemy, std::weak_ptr<BoxCollider> base )
	{
		enemy.lock()->parentPointer->SetWishDelete( true );
		dynamic_cast<PlayerBase*>( base.lock()->parentPointer )->GetPlayerPtr().lock()->AddBaseDamage( 1 );
	}
}