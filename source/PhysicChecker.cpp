/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "PhysicChecker.hpp"

namespace kd
{
	void PhysicChecker::removeUnusedEntities()
	{
		for (auto it = colliders.begin(); it != colliders.end();)
		{
			if ((*it)->parentPointer->isWishingDelete())
				it = colliders.erase(it);
			else
				it++;
		}
	}

	bool PhysicChecker::collidedLeft(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b)
	{
		return a_old.left + a_old.width < b.left &&
			a.left + a.width >= b.left;
	}

	bool PhysicChecker::collidedRight(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b)
	{
		return a_old.left >= b.left + b.width &&
			a.left < b.left + b.width;
	}

	bool PhysicChecker::collidedTop(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b)
	{
		return a_old.top + a_old.height < b.top &&
			a.top + a.height >= b.top;
	}

	bool PhysicChecker::collidedBottom(const sf::FloatRect& a, const sf::FloatRect& a_old, const sf::FloatRect& b)
	{
		return a_old.top >= b.top + b.height &&
			a.top < b.top + b.height;
	}

	bool PhysicChecker::addBoxCollider(std::shared_ptr<BoxCollider> collider)
	{
		if (!collider)
		{
			cgf::Logger::log("Cannot add collider to PhysicChecer - collider pointer is not assigned", cgf::Logger::ERROR);
		}

		for (auto ptr : colliders)
			if (ptr == collider)
			{
				cgf::Logger::log("Cannot add collider to PhysicChecker - found pointer pointing to same collider", cgf::Logger::ERROR);
				return false;
			}

		colliders.push_back(collider);

		cgf::Logger::log("Added collider to PhysicChecker, total colliders: " + std::to_string(colliders.size()));
		
		return true;
	}

	void PhysicChecker::update(seconds_t dt)
	{
		removeUnusedEntities();

		for (size_t i = 0; i < colliders.size(); ++i)
			for (size_t j = 0; j < colliders.size(); ++j)
			{
				if(i == j)
					continue;

				sf::FloatRect& collA = colliders[i]->rectangle;
				sf::FloatRect collAupdated = collA;
				collAupdated.left += colliders[i]->velocity.x * dt;
				collAupdated.top += colliders[i]->velocity.y * dt;
				sf::FloatRect& collB = colliders[j]->rectangle;

				if(!collAupdated.intersects(collB))
					continue;

				collision_side_t collAside = None;

				if (collidedLeft(collAupdated, collA, collB))
					collAside = Left;
				else if (collidedRight(collAupdated, collA, collB))
					collAside = Right;
				else if (collidedTop(collAupdated, collA, collB))
					collAside = Top;
				else if (collidedBottom(collAupdated, collA, collB))
					collAside = Down;

				/* Temporary */
				cgf::Logger::log("Collision side:" + std::to_string(collAside), cgf::Logger::INFO, cgf::Logger::CONSOLE);
			}
	}
}