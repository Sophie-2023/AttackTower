#pragma once

#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "TroupeManager.h"
#include "TroupeFactory.h"
#include "Carte.h"

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
  void updateTimer(sf::Time elapsedTime);


  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

  static const float PlayerSpeed;
  static const sf::Time TimePerFrame;

  sf::RenderWindow mWindow{sf::VideoMode({1000, 700}), "Attack Tower Game"};
  sf::Texture mTexture;
  
  Carte carte;
  TroupeManager troupeManager;

  // affichage du timer
  sf::Time timer{sf::Time::Zero};
  int secondes{400};
  sf::Font font;
  sf::Text affichageTimer;


  Troupe *troupeSelectionnee = nullptr;

  bool mIsMovingUp{false};
  bool mIsMovingDown{false};
  bool mIsMovingRight{false};
  bool mIsMovingLeft{false};
};

#endif  // BOOK_GAME_HPP
