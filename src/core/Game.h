#pragma once

#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "TroupeManager.h"
#include "TroupeFactory.h"

class Game {
 public:
  Game();
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  void run();

 private:
  void processEvents();
  void update(sf::Time elapsedTime);
  void render();

  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

  static const float PlayerSpeed;
  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow{sf::VideoMode({1000, 700}), "Attack Tower Game"};
  sf::Texture mTexture;
  
  TroupeManager troupeManager;
  TroupeFactory troupeFactory;

  bool mIsMovingUp{false};
  bool mIsMovingDown{false};
  bool mIsMovingRight{false};
  bool mIsMovingLeft{false};
};

#endif  // BOOK_GAME_HPP
