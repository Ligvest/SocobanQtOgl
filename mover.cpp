#include "mover.hpp"
#include <iostream>

Mover::Mover() {}

Mover::Mover(Map* map) {
    map_ = map;
    sMap_ = map_->mapAsString();
}

bool Mover::setTile(Point pos, Map::eTile tileToSet) {
    // If one of objects is over the border of sMap_
    if (pos.y() * map_->mapColumns() + pos.x() > sMap_.size() - 1) {
        return false;
    }

    sMap_[pos.y() * map_->mapColumns() + pos.x()] = tileToChar(tileToSet);
}

// Move boxes
bool Mover::mergeBox(Point posFrom, Point posTo) {
    Map::eTile tileFrom = getTile(posFrom);

    if (tileFrom == Map::eTile::BOX_ON_GOAL) {
        setTile(posFrom, Map::eTile::GOAL);
        setTile(posTo, Map::eTile::BOX_ON_GOAL);
    } else if (tileFrom == Map::eTile::BOX) {
        setTile(posFrom, Map::eTile::FLOOR);
        setTile(posTo, Map::eTile::BOX_ON_GOAL);
    }
    return true;
}

bool Mover::moveBoxFromFloor(Point posFrom, Point posTo) {
    Map::eTile tileTo = getTile(posTo);
    if (tileTo == Map::eTile::FLOOR) {
        swapObjects(posFrom, posTo);
        return true;
    } else if (tileTo == Map::eTile::GOAL) {
        mergeBox(posFrom, posTo);
        return true;
    } else {
        return false;
    }
}

bool Mover::moveBoxFromGoal(Point posFrom, Point posTo) {
    setTile(posFrom, Map::eTile::BOX);
    if (moveBoxFromFloor(posFrom, posTo)) {
        setTile(posFrom, Map::eTile::GOAL);
        return true;
    } else {
        setTile(posFrom, Map::eTile::BOX_ON_GOAL);
        return false;
    }
}

bool Mover::moveBoxFromTo(Point posFrom, Point posTo) {
    Map::eTile tileFrom = getTile(posFrom);
    if (tileFrom == Map::eTile::BOX) {
        return moveBoxFromFloor(posFrom, posTo);
    } else if (tileFrom == Map::eTile::BOX_ON_GOAL) {
        return moveBoxFromGoal(posFrom, posTo);
    }
}
// <! Move boxes

// Move player
bool Mover::mergePlayer(Point posFrom, Point posTo) {
    setTile(posFrom, Map::eTile::FLOOR);
    setTile(posTo, Map::eTile::PLAYER_ON_GOAL);
    return true;
}

bool Mover::movePlayerFromFloor(Point posFrom, Point posTo) {
    Map::eTile tileTo = getTile(posTo);
    Point posDirection = posTo - posFrom;
    Point posAfterPosTo = posTo + posDirection;

    if (tileTo == Map::eTile::FLOOR) {
        return swapObjects(posFrom, posTo);
    } else if (tileTo == Map::eTile::BOX) {
        if (moveBoxFromTo(posTo, posAfterPosTo)) {
            return swapObjects(posFrom, posTo);
        } else {
            return false;
        }
    } else if (tileTo == Map::eTile::BOX_ON_GOAL) {
        if (moveBoxFromTo(posTo, posAfterPosTo)) {
            return mergePlayer(posFrom, posTo);
        } else {
            return false;
        }
    } else if (tileTo == Map::eTile::GOAL) {
        return mergePlayer(posFrom, posTo);
    } else {
        return false;
    }
}

bool Mover::movePlayerFromGoal(Point posFrom, Point posTo) {
    setTile(posFrom, Map::eTile::PLAYER);
    if (movePlayerFromFloor(posFrom, posTo)) {
        setTile(posFrom, Map::eTile::GOAL);
        return true;
    } else {
        setTile(posFrom, Map::eTile::PLAYER_ON_GOAL);
        return false;
    }
}

bool Mover::movePlayerFromTo(Point posFrom, Point posTo) {
    Map::eTile tileFrom = getTile(posFrom);
    if (tileFrom == Map::eTile::PLAYER_ON_GOAL) {
        movePlayerFromGoal(posFrom, posTo);
    } else if (tileFrom == Map::eTile::PLAYER) {
        movePlayerFromFloor(posFrom, posTo);
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
    return movePlayerFromTo(posPlayer, posUnderPlayer);
}

bool Mover::movePlayerRight() {
    Point posPlayer(map_->playerX(), map_->playerY());
    Point posRightFromPlayer(posPlayer.x() + 1, posPlayer.y());
    return movePlayerFromTo(posPlayer, posRightFromPlayer);
}

bool Mover::movePlayerLeft() {
    Point posPlayer(map_->playerX(), map_->playerY());
    Point posLeftFromPlayer(posPlayer.x() - 1, posPlayer.y());
    return movePlayerFromTo(posPlayer, posLeftFromPlayer);
}
//<! Move player

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
