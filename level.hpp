#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include "map.hpp"
#include "mover.hpp"
#include "point.hpp"

class Level {
   public:
    Level(int iWidth, int iHeight, std::string sName, std::string sMap);
    ~Level();
    int columns() const;
    int rows() const;
    std::string name() const;
    const Map& map() const;

    // Control functions
    void reset();
    void load(int iLevelNumber);
    void load(std::string sFileWithSave);
    bool isComplete() const;
    bool isLoaded() const;

    void playerUp();
    void playerDown();
    void playerLeft();
    void playerRight();

    int stepsPerformed() const;
    int goals() const;
    int boxesOnGoals() const;

   private:
    int iNumOfColumns_;
    int iNumOfRows_;
    std::string sName_;
    Map map_;

    int iStepsPerformed_;
    int iGoals_;
    int iBoxesOnGoals_;

    bool isComplete_;
    bool isLoaded_;

    Point playerPosition_;
};

#endif  // LEVEL_HPP
