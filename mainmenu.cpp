#include "mainmenu.hpp"

MainMenu::MainMenu()
    : curItem_(eMenuItem((static_cast<int>(eMenuItem::START) + 1))) {
  InitVecMenu();
}

MainMenu::eMenuItem MainMenu::curItem() const { return curItem_; }

const std::vector<std::pair<MainMenu::eMenuItem, std::string>>&
MainMenu::vecMenu() const {
  return vecMenu_;
}

void MainMenu::nextItem() {
  curItem_ = eMenuItem((static_cast<int>(curItem_) + 1));
  if (curItem_ == eMenuItem::END) {
    curItem_ = eMenuItem((static_cast<int>(eMenuItem::START) + 1));
  }
}

void MainMenu::prevItem() {
  curItem_ = eMenuItem((static_cast<int>(curItem_) - 1));
  if (curItem_ == eMenuItem::START) {
    curItem_ = eMenuItem((static_cast<int>(eMenuItem::END) - 1));
  }
}

GameState::eState MainMenu::toStateEnum() {
  switch (curItem_) {
    case eMenuItem::PLAY:
      return GameState::eState::PLAY;
      break;
    case eMenuItem::SELECT_LEVEL:
      return GameState::eState::SELECT_LEVEL;
      break;
    case eMenuItem::PLAYER_STAT:
      return GameState::eState::PLAYER_STATS;
      break;
    case eMenuItem::EXIT:
      return GameState::eState::EXIT;
      break;
    default:
      break;
  }
}

void MainMenu::InitVecMenu() {
  vecMenu_.push_back({eMenuItem::PLAY, "Play"});
  vecMenu_.push_back({eMenuItem::SELECT_LEVEL, "Select level"});
  vecMenu_.push_back({eMenuItem::PLAYER_STAT, "Statistics"});
  vecMenu_.push_back({eMenuItem::EXIT, "Exit"});
}
