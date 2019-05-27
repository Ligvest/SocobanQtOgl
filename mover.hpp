#ifndef MOVER_HPP
#define MOVER_HPP

#include "map.hpp"

class Mover {
    enum class eDirections { UP, Down, Right, Left };

   public:
    Mover(Map* map);
    bool moveBoxUp(int iBoxRow, int iBoxColumn);
    bool moveBoxDown(int iBoxRow, int iBoxColumn);
    bool moveBoxRight(int iBoxRow, int iBoxColumn);
    bool moveBoxLeft(int iBoxRow, int iBoxColumn);
    bool movePlayerUp();
    bool movePlayerDown();
    bool movePlayerRight();
    bool movePlayerLeft();
    Map::eTile getTile(int iTileRow, int iTileColumn);

   private:
    Mover();
    bool isObjectStatic(int iTileRow, int iTileColumn);
    bool swapObjects(int iFirstTileRow, int iFirstTileColumn,
                     int iSecondTileRow, int iSecondTileColumn);

   private:
    Map* map_;
    std::string sMap_;
};

#endif  // MOVER_HPP
