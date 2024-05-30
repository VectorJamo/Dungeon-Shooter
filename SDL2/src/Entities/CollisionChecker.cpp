#include "CollisionChecker.h"

#include <iostream>

CollisionAxes checkCollision(const Entity& entity, const Entity& entity2, float dx, float dy) {
    return CollisionAxes();
}

CollisionAxes checkCollision(Entity* entity, Tilemap* tileMap, float dx, float dy) {
    CollisionAxes type;
    type.xCollision = false;
    type.yCollision = false;

    for (int i = 0; i < tileMap->getMapRows(); i++) {
        for (int j = 0; j < tileMap->getMapCols(); j++) {

            unsigned char** tiles = tileMap->getTileMap();

            if (tiles[i][j] != '0') {
                int tileX = j * tileMap->getTileSize();
                int tileY = i * tileMap->getTileSize();

                // First set the player's X to the new X and check if collision occurs,
                float entityXNew = (entity->getXPos() + entity->getCollideRect().x) + dx;
                if (!(entityXNew > tileX + tileMap->getTileSize() || entityXNew + (entity->getCollideRect().w) < tileX || (entity->getYPos() + entity->getCollideRect().y) + entity->getCollideRect().h < tileY ||
                    entity->getYPos() + entity->getCollideRect().y > tileY + tileMap->getTileSize())) {
                    type.xCollision = true;
                }
                // Then, set the player's Y to the new Y and check if collision occurs
                float entityYNew = (entity->getYPos() + entity->getCollideRect().y) + dy;
                if (!(entity->getXPos() + entity->getCollideRect().x > tileX + tileMap->getTileSize() || (entity->getXPos() + entity->getCollideRect().x) + entity->getCollideRect().w < tileX ||
                    (entityYNew + entity->getCollideRect().h) < tileY || entityYNew > tileY + tileMap->getTileSize())) {
                    type.yCollision = true;
                }
            }
        }
    }
    return type;
}

// For laser
bool checkCollision(int worldX, int worldY, int width, int height, Tilemap* tileMap) {
    for (int i = 0; i < tileMap->getMapRows(); i++) {
        for (int j = 0; j < tileMap->getMapCols(); j++) {

            unsigned char** tiles = tileMap->getTileMap();

            if (tiles[i][j] != '0') {
                int tileX = j * tileMap->getTileSize();
                int tileY = i * tileMap->getTileSize();

                if (!(worldX > tileX + tileMap->getTileSize() || worldX + width < tileX || worldY + height < tileY ||
                    worldY > tileY + tileMap->getTileSize())) {
                    return true;
                }
            }
        }
    }
    return false;
}
   
