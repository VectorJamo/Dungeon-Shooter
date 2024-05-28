#pragma once

#include "Entity.h"
#include "Player.h"
#include "../tilemap/Tilemap.h"

struct CollisionAxes {
	bool xCollision = true, yCollision = true;
};

CollisionAxes checkCollision(const Entity* entity1, const Entity* entity2, float dx, float dy);
CollisionAxes checkCollision(Entity* entity, Tilemap* tileMap, float dx, float dy);