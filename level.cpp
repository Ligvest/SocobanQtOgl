#include "level.hpp"
#include <algorithm>

Level::Level(int iWidth, int iHeight, std::string sName, std::string sMap)
    : map_(sMap, iWidth, iHeight), playerPosition_(Point(0, 0)) {
    iNumOfColumns_ = iWidth;
    iNumOfRows_ = iHeight;
    sName_ = sName;

    iStepsPerformed_ = 0;
    iGoals_ = std::count(sMap.begin(), sMap.end(), '.');
    iBoxesOnGoals_ = 0;
    isComplete_ = false;
}

Level::~Level() {}

int Level::columns() const { return iNumOfColumns_; }

int Level::rows() const { return iNumOfRows_; }

std::string Level::name() const { return sName_; }

const Map& Level::map() const { return map_; }

void Level::reset() {}

void Level::load(int iLevelNumber) {}

void Level::load(std::string sFileWithSave) {}

bool Level::isComplete() const {}

bool Level::isLoaded() const {}

void Level::playerUp() {
    Mover mover(&map_);
    mover.movePlayerUp();
}

void Level::playerDown() {
    Mover mover(&map_);
    mover.movePlayerDown();
}

void Level::playerLeft() {
    Mover mover(&map_);
    mover.movePlayerLeft();
}

void Level::playerRight() {
    Mover mover(&map_);
    mover.movePlayerRight();
}

int Level::stepsPerformed() const { return iStepsPerformed_; }

int Level::goals() const { return iGoals_; }

int Level::boxesOnGoals() const { return iBoxesOnGoals_; }
