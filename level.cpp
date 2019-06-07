#include "level.hpp"
#include <algorithm>
#include "movercountdecorator.hpp"

Level::Level(int iWidth, int iHeight, std::string sName, std::string sMap)
    : map_(sMap, iWidth, iHeight), playerPosition_(Point(0, 0)) {
    iNumOfColumns_ = iWidth;
    iNumOfRows_ = iHeight;
    sName_ = sName;

    iStepsPerformed_ = 0;
    iGoals_ = map_.goals();
    iBoxesOnGoals_ = map_.boxesOnGoals();
    isComplete_ = false;
}

Level::~Level() {}

int Level::columns() const { return iNumOfColumns_; }

int Level::rows() const { return iNumOfRows_; }

std::string Level::name() const { return sName_; }

const Map& Level::map() const { return map_; }

void Level::resetLevel() {
    map_.ResetMap();
    iStepsPerformed_ = 0;
    iBoxesOnGoals_ = map_.boxesOnGoals();
    isComplete_ = false;
}

void Level::load(int iLevelNumber) {}

void Level::load(std::string sFileWithSave) {}

bool Level::isComplete() const { return isComplete_; }

bool Level::isLoaded() const {}

void Level::playerUp() {
    Mover mover(&map_);
    MoverCountDecorator moverCount(&mover);
    moverCount.movePlayerUp(iStepsPerformed_);
    setBoxesOnGoals(map_.boxesOnGoals());
}

void Level::playerDown() {
    Mover mover(&map_);
    MoverCountDecorator moverCount(&mover);
    moverCount.movePlayerDown(iStepsPerformed_);
    setBoxesOnGoals(map_.boxesOnGoals());
}

void Level::playerLeft() {
    Mover mover(&map_);
    MoverCountDecorator moverCount(&mover);
    moverCount.movePlayerLeft(iStepsPerformed_);
    setBoxesOnGoals(map_.boxesOnGoals());
}

void Level::playerRight() {
    Mover mover(&map_);
    MoverCountDecorator moverCount(&mover);
    moverCount.movePlayerRight(iStepsPerformed_);
    setBoxesOnGoals(map_.boxesOnGoals());
}

int Level::stepsPerformed() const { return iStepsPerformed_; }

int Level::goals() const { return iGoals_; }

int Level::boxesOnGoals() const { return iBoxesOnGoals_; }

void Level::setBoxesOnGoals(int value) {
    iBoxesOnGoals_ = value;
    if (iBoxesOnGoals_ == iGoals_) {
        isComplete_ = true;
    }
}
