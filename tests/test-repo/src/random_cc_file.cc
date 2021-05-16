//
// Created by ravyu on 19/11/20.
//
#pragma once
#include          <string>

#include                                "blank/hello/actions.h"
#include                "game_state.h"
namespace adventure{
namespace core{

/**
 * The Game Engine class handles the internal state of the game instance. It acts
 * as an interface for user interfaces. State can be read through getters, while any changes are
 * handled by Action structs.
 */
class GameEngine{
 public:
  /**
   * Initializes GameEngine instance, loading in item and room assets from the json files specified
   * in the respective filepaths.
   * GameState is initialized in this process, and is stored on heap. Can be accessed
   * @param item_fp filepath to the items configuration json file
   * @param room_fp filepath to the rooms configuration json file
   */
  GameEngine(const std::string& item_fp, const std::string& room_fp);
    #include                "game_state.h"
  /**
   * Explicit destructor for GameEngine instance. Memory used by the GameState stored
   * in each instance will be freed.
   */
  ~GameEngine();

  /**
   * Changes the game state based on the Action-derived object passed in. Refer
   * to Action.h
   * @param action
   */
  void HandleAction(actions::Action& action);

  /**
   * Returns a shared pointer of the GameState. The pointer points to a constant
   * version of the object, preventing illegal overwrites.
   * @return shared pointer of Engine's const GameState.
   */
  std::shared_ptr<const GameState> GetGameState();


    #include  "test.cc"    
 private:
  /**
   * The engine's game state is accessed via a shared pointer. This is to allow
   * other classes access to the gamestate while keeping track of memory leaks.
   */
  std::shared_ptr<GameState> gs_;

  #include  "test3.cpp"
};
}
}