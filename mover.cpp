#include "mover.hpp"
#include <iostream>

Mover::Mover() {}

Mover::Mover(Map* map) {
    map_ = map;
    std::cout << map_->playerX() << std::endl;
    sMap_ = map_->mapAsString();
}

bool Mover::moveBoxUp(int iBoxRow, int iBoxColumn) {
    if (getTile(iBoxRow - 1, iBoxColumn) == Map::eTile::FLOOR) {
        swapObjects(iBoxRow, iBoxColumn, iBoxRow - 1, iBoxColumn);
        return true;
    } else {
        return false;
    }
}

bool Mover::moveBoxDown(int iBoxRow, int iBoxColumn) {}

bool Mover::moveBoxRight(int iBoxRow, int iBoxColumn) {}

bool Mover::moveBoxLeft(int iBoxRow, int iBoxColumn) {}

bool Mover::movePlayerUp() {
    int iPlayerY = map_->playerY();
    int iPlayerX = map_->playerX();
    std::cout << "from Mover iPlayerY and X: " << iPlayerY << " and "
              << iPlayerX << std::endl;

    Map::eTile tileAbove = getTile(iPlayerY - 1, iPlayerX);
    if (tileAbove == Map::eTile::BOX) {
        if (moveBoxUp(iPlayerY - 1, iPlayerX)) {
            swapObjects(iPlayerY, iPlayerX, iPlayerY - 1, iPlayerX);
        } else {
            return false;
        }
    } else if (tileAbove == Map::eTile::FLOOR) {
        swapObjects(iPlayerY, iPlayerX, iPlayerY - 1, iPlayerX);
    } else {
        return false;
    }

    map_->setMapString(sMap_);
    map_->buildMap();
    return true;
}

bool Mover::movePlayerDown() {}

bool Mover::movePlayerRight() {}

bool Mover::movePlayerLeft() {}

Map::eTile Mover::getTile(int iTileRow, int iTileColumn) {
    int iTilePosition = iTileRow * map_->mapColumns() + iTileColumn;
    if (iTilePosition >= sMap_.size()) {
        return Map::eTile::WALL;
    }
    char cTile = sMap_[iTilePosition];
    Map::eTile tile;
    switch (cTile) {
        case '#':
            tile = Map::eTile::WALL;
            break;
        case '@':
            tile = Map::eTile::PLAYER;
            break;
        case '+':
            tile = Map::eTile::PLAYER_ON_GOAL;
            break;
        case '$':
            tile = Map::eTile::BOX;
            break;
        case '*':
            tile = Map::eTile::BOX_ON_GOAL;
            break;
        case '.':
            tile = Map::eTile::GOAL;
            break;
        case ' ':
            tile = Map::eTile::FLOOR;
            break;
        default:
            tile = Map::eTile::FLOOR;
            break;
    }
    return tile;
}

bool Mover::isObjectStatic(int iTileRow, int iTileColumn) {
    switch (sMap_[iTileRow * map_->mapColumns() + iTileColumn]) {
        case '#':  // wall
        case '.':  // goal
        case ' ':  // floor
            return true;
        case '@':  // player
        case '+':  // player on a goal
        case '$':  // box
        case '*':  // box on a goal
            return false;
        default:
            return true;
            break;
    }
}

bool Mover::swapObjects(int iFirstTileRow, int iFirstTileColumn,
                        int iSecondTileRow, int iSecondTileColumn) {
    // If one of objects is over the border of sMap_
    if (iFirstTileRow * map_->mapColumns() + iFirstTileColumn >
        sMap_.size() - 1) {
        return false;
    }
    if (iSecondTileRow * map_->mapColumns() + iSecondTileColumn >
        sMap_.size() - 1) {
        return false;
    }

    //    isObjectStatic(iSecondTileRow, iSecondTileColumn);
    //    isObjectStatic(iFirstTileRow, iFirstTileColumn);

    char cTempTile =
        sMap_[iFirstTileRow * map_->mapColumns() + iFirstTileColumn];
    sMap_[iFirstTileRow * map_->mapColumns() + iFirstTileColumn] =
        sMap_[iSecondTileRow * map_->mapColumns() + iSecondTileColumn];
    sMap_[iSecondTileRow * map_->mapColumns() + iSecondTileColumn] = cTempTile;
    return true;
}
