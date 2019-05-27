#ifndef SELECTLEVELMENU_HPP
#define SELECTLEVELMENU_HPP
#include <list>
#include <vector>
#include "level.hpp"

class SelectLevelMenu {
 public:
  SelectLevelMenu(const std::vector<Level>* pVecLevels);

  int curItem() const;
  Level curLevel() const;

  void nextItem();
  void prevItem();

  int minDisplayedItem() const;
  void setMinDisplayedItem(int iMinDisplayedItem);

  int maxDisplayedItem() const;
  void setMaxDisplayedItem(int iMaxDisplayedItem);

  void updateRangeToDisplay();

  std::list<std::pair<int, std::string>> rangeToDisplay() const;

 private:
  int iCurItem_;
  int iMinDisplayedItem_;
  int iMaxDisplayedItem_;

  const std::vector<Level>* pVecLevels_;
  std::list<std::pair<int, std::string>> listRangeToDisplay_;
};

#endif  // SELECTLEVELMENU_HPP
