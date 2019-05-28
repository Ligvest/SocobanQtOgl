#include "mover.hpp"
#include <iostream>

Mover::Mover() {}

Mover::Mover(Map* map) {
    map_ = map;
    sMap_ = map_->mapAsString();
    std::cout << "Mover:  " << map << std::endl;
}

bool Mover::setTile(Point pos, Map::eTile tileToSet) {
    // If one of objects is over the border of sMap_
    if (pos.y() * map_->mapColumns() + pos.x() > sMap_.size() - 1) {
        return false;
    }

    sMap_[pos.y() * map_->mapColumns() + pos.x()] = tileToChar(tileToSet);
}

bool Mover::mergeObjects(Point posFrom, Point posTo) {
    if (getTile(posFrom) == Map::eTile::BOX &&
        getTile(posTo) == Map::eTile::GOAL) {
        setTile(posFrom, Map::eTile::FLOOR);
        setTile(posTo, Map::eTile::BOX_ON_GOAL);
        return true;
    } else if (getTile(posFrom) == Map::eTile::PLAYER &&
               getTile(posTo) == Map::eTile::GOAL) {
        setTile(posFrom, Map::eTile::FLOOR);
        setTile(posTo, Map::eTile::PLAYER_ON_GOAL);
        return true;
    } else {
        return false;
    }
}

bool Mover::moveBoxFromTo(Point posFrom, Point posTo) {
    if (getTile(posTo) == Map::eTile::FLOOR) {
        swapObjects(posFrom, posTo);
        return true;
    } else if (getTile(posTo) == Map::eTile::GOAL) {
        mergeObjects(posFrom, posTo);
        return true;
    } else {
        return false;
    }
}
bool Mover::moveBoxUp(Point posBox) {
    Point posAboveBox(posBox.x(), posBox.y() - 1);
    moveBoxFromTo(posBox, posAboveBox);
}

bool Mover::moveBoxDown(Point posBox) {
    Point posUnderBox(posBox.x(), posBox.y() + 1);
    moveBoxFromTo(posBox, posUnderBox);
}

bool Mover::moveBoxRight(Point posBox) {
    Point posRightFromBox(posBox.x() + 1, posBox.y());
    moveBoxFromTo(posBox, posRightFromBox);
}

bool Mover::moveBoxLeft(Point posBox) {
    Point posLeftFromBox(posBox.x() - 1, posBox.y());
    moveBoxFromTo(posBox, posLeftFromBox);
}

bool Mover::movePlayerFromTo(Point posFrom, Point posTo) {
    Map::eTile tileTo = getTile(posTo);
    Point posDirection = posTo - posFrom;
    Point posAfterPosTo = posTo + posDirection;
    if (tileTo == Map::eTile::BOX || tileTo == Map::eTile::BOX_ON_GOAL) {
        if (moveBoxFromTo(posTo, posAfterPosTo)) {
            swapObjects(posFrom, posTo);
        } else {
            return false;
        }
    } else if (tileTo == Map::eTile::FLOOR) {
        swapObjects(posFrom, posTo);
    } else {
        return false;
    }

    map_->setMapString(sMap_);
    map_->buildMap();
    return true;
}

bool Mover::movePlayerUp() {
    Point posPlayer(map_->playerX(), map_->playerY());
    Point posAbovePlayer(posPlayer.x(), posPlayer.y() - 1);
    movePlayerFromTo(posPlayer, posAbovePlayer);
}

bool Mover::movePlayerDown() {
    Point posPlayer(map_->playerX(), map_->playerY());
    Point posUnderPlayer(posPlayer.x(), posPlayer.y() + 1);
    movePlayerFromTo(posPlayer, posUnderPlayer);
}

bool Mover::movePlayerRight() {
    Point posPlayer(map_->playerX(), map_->playerY());
    Point posRightFromPlayer(posPlayer.x() + 1, posPlayer.y());
    movePlayerFromTo(posPlayer, posRightFromPlayer);
}

bool Mover::movePlayerLeft() {
    Point posPlayer(map_->playerX(), map_->playerY());
    Point posLeftFromPlayer(posPlayer.x() - 1, posPlayer.y());
    movePlayerFromTo(posPlayer, posLeftFromPlayer);
}

Map::eTile Mover::getTile(Point posTile) {
    int iTileRow = posTile.y();
    int iTileColumn = posTile.x();
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

char Mover::tileToChar(Map::eTile tileToConvert) {
    char cTile = ' ';
    switch (tileToConvert) {
        case Map::eTile::WALL:
            cTile = '#';
            break;
        case Map::eTile::PLAYER:
            cTile = '@';
            break;
        case Map::eTile::PLAYER_ON_GOAL:
            cTile = '+';
            break;
        case Map::eTile::BOX:
            cTile = '$';
            break;
        case Map::eTile::BOX_ON_GOAL:
            cTile = '*';
            break;
        case Map::eTile::GOAL:
            cTile = '.';
            break;
        case Map::eTile::FLOOR:
            cTile = ' ';
            break;
        default:
            cTile = ' ';
            break;
    }
    return cTile;
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

bool Mover::swapObjects(Point posFirstObj, Point posSecondObj) {
    // If one of objects is over the border of sMap_
    if (posFirstObj.y() * map_->mapColumns() + posFirstObj.x() >
        sMap_.size() - 1) {
        return false;
    }
    if (posSecondObj.y() * map_->mapColumns() + posSecondObj.x() >
        sMap_.size() - 1) {
        return false;
    }

    char cTempTile =
        sMap_[posFirstObj.y() * map_->mapColumns() + posFirstObj.x()];
    sMap_[posFirstObj.y() * map_->mapColumns() + posFirstObj.x()] =
        sMap_[posSecondObj.y() * map_->mapColumns() + posSecondObj.x()];
    sMap_[posSecondObj.y() * map_->mapColumns() + posSecondObj.x()] = cTempTile;
    return true;
}
