#include "gamestate.hpp"

GameState::GameState() { curState_ = eState::MENU; }

GameState::eState GameState::curState() { return curState_; }

void GameState::setState(GameState::eState newState) { curState_ = newState; }
