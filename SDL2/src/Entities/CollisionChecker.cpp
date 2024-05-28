#include "CollisionChecker.h"

#include <iostream>

CollisionAxes checkCollision(const Entity& entity1, const Entity& entity2, float dx, float dy) {
    return CollisionAxes();
}

CollisionAxes checkCollision(Entity* entity, Tilemap* tileMap, float dx, float dy) {
    CollisionAxes type;
    type.xCollision = false;
    type.yCollision = false;

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {

            unsigned char** tiles = tileMap->getTileMap();

            if (tiles[i][j] != '0') {
                int tileX = j * tileMap->getTileSize();
                int tileY = i * tileMap->getTileSize();

                // First set the player's X to the new X and check if collision occurs,
                float entityXNew = entity->getXPos() + dx;
                if (!(entityXNew > tileX + tileMap->getTileSize() || entityXNew + entity->getWidth() < tileX || entity->getYPos() + entity->getHeight() < tileY ||
                    entity->getYPos() > tileY + tileMap->getTileSize())) {
                    type.xCollision = true;
                }
                // Then, set the player's Y to the new Y and check if collision occurs
                float entityYNew = entity->getYPos() + dy;
                if (!(entity->getXPos() > tileX + tileMap->getTileSize() || entity->getXPos() + entity->getWidth() < tileX ||
                    entityYNew + entity->getHeight() < tileY || entityYNew > tileY + tileMap->getTileSize())) {
                    type.yCollision = true;
                }
            }
        }
    }
    return type;
}
   
