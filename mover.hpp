#ifndef MOVER_HPP
#define MOVER_HPP

#include "map.hpp"
#include "point.hpp"

class Mover {
    enum class eDirections { UP, Down, Right, Left };

   public:
    Mover(Map* map);

    // Move the player
    bool movePlayerUp();
    bool movePlayerDown();
    bool movePlayerRight();
    bool movePlayerLeft();

   private:
    Mover();
    bool swapObjects(Point posFirstObj, Point posSecondObj);
    bool setTile(Point pos, Map::eTile tileToSet);
    char tileToChar(Map::eTile tileToConvert);
    Map::eTile getTile(Point posTile);

    // Move a box
    bool moveBoxFromTo(Point posFrom, Point posTo);
    bool moveBoxFromFloor(Point posFrom, Point posTo);
    bool moveBoxFromGoal(Point posFrom, Point posTo);
    bool mergeBox(Point posFrom, Point posTo);

    // Move the player
    bool movePlayerFromTo(Point posFrom, Point posTo);
    bool movePlayerFromFloor(Point posFrom, Point posTo);
    bool movePlayerFromGoal(Point posFrom, Point posTo);
    bool mergePlayer(Point posFrom, Point posTo);

   private:
    Map* map_;
    std::string sMap_;
};

#endif  // MOVER_HPP
