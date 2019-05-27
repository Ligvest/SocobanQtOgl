#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameState {
 public:
  enum class eState { MENU, SELECT_LEVEL, PLAYER_STATS, PLAY, EXIT };
  GameState();
  eState curState();
  void setState(eState newState);

 private:
  eState curState_;
};

#endif  // GAMESTATE_HPP
