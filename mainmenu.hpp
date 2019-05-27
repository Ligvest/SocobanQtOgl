#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <string>
#include <vector>
#include "gamestate.hpp"

class MainMenu {
 public:
  enum class eMenuItem {
    START = -1,
    PLAY,
    SELECT_LEVEL,
    PLAYER_STAT,
    EXIT,
    END
  };

  MainMenu();
  eMenuItem curItem() const;
  const std::vector<std::pair<eMenuItem, std::string>>& vecMenu() const;
  void nextItem();
  void prevItem();
  GameState::eState toStateEnum();

 private:
  void InitVecMenu();

 private:
  eMenuItem curItem_;
  std::vector<std::pair<eMenuItem, std::string>> vecMenu_;
};

#endif  // MAINMENU_HPP
