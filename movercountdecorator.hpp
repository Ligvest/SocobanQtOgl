#ifndef MOVERCOUNTDECORATOR_HPP
#define MOVERCOUNTDECORATOR_HPP

#include "map.hpp"
#include "mover.hpp"
#include "point.hpp"

class MoverCountDecorator {
   public:
    MoverCountDecorator(Mover* pMover);

    // Move the player
    bool movePlayerUp(int& iNumOfSteps);
    bool movePlayerDown(int& iNumOfSteps);
    bool movePlayerRight(int& iNumOfSteps);
    bool movePlayerLeft(int& iNumOfSteps);

    Mover* pMover_;
};

#endif  // MOVERCOUNTDECORATOR_HPP
