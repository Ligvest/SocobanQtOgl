#ifndef MOVER_HPP
#define MOVER_HPP

#include "map.hpp"
#include "point.hpp"

class Mover {
    enum class eDirections { UP, Down, Right, Left };

   public:
    Mover(Map* map);
    bool movePlayerUp();
    bool movePlayerDown();
    bool movePlayerRight();
    bool movePlayerLeft();
    Map::eTile getTile(Point posTile);

   private:
    Mover();
    bool isObjectStatic(int iTileRow, int iTileColumn);
    bool swapObjects(Point posFirstObj, Point posSecondObj);
    bool moveBoxUp(Point posBox);
    bool moveBoxDown(Point posBox);
    bool moveBoxRight(Point posBox);
    bool moveBoxLeft(Point posBox);
    bool moveBoxFromTo(Point posFrom, Point posTo);
    bool movePlayerFromTo(Point posFrom, Point posTo);
    bool mergeObjects(Point posFrom, Point posTo);
    bool setTile(Point pos, Map::eTile tileToSet);
    char tileToChar(Map::eTile tileToConvert);

   private:
    Map* map_;
    std::string sMap_;
};

#endif  // MOVER_HPP
