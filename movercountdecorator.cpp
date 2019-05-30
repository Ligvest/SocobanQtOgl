#include "movercountdecorator.hpp"

MoverCountDecorator::MoverCountDecorator(Mover* pMover) { pMover_ = pMover; }

bool MoverCountDecorator::movePlayerUp(int& iNumOfSteps) {
    if (pMover_->movePlayerUp()) {
        ++iNumOfSteps;
        return true;
    } else {
        return false;
    }
}

bool MoverCountDecorator::movePlayerDown(int& iNumOfSteps) {
    if (pMover_->movePlayerDown()) {
        ++iNumOfSteps;
        return true;
    } else {
        return false;
    }
}

bool MoverCountDecorator::movePlayerRight(int& iNumOfSteps) {
    if (pMover_->movePlayerRight()) {
        ++iNumOfSteps;
        return true;
    } else {
        return false;
    }
}

bool MoverCountDecorator::movePlayerLeft(int& iNumOfSteps) {
    if (pMover_->movePlayerLeft()) {
        ++iNumOfSteps;
        return true;
    } else {
        return false;
    }
}
