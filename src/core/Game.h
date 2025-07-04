#pragma once

#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "TroupeManager.h"
#include "TroupeFactory.h"
#include "Carte.h"

class Game {
 public:
  Game(sf::RenderWindow& window);
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  int run();

  void setEnd(bool win);
  void setTroupeSelectionnee(Troupe *troupe) { troupeSelectionnee = troupe; }
  Troupe *getTroupeSelectionnee() const { return troupeSelectionnee; }

 private:
  void processEvents();
  void update(sf::Time elapsedTime);
  void render();
  void updateTimer(sf::Time elapsedTime);

  bool end=false;
  bool win;

  static const float PlayerSpeed;
  static const sf::Time TimePerFrame;

  sf::RenderWindow& mWindow;
  sf::Texture mTexture;
  
  Carte carte;
  TroupeManager troupeManager;

  // affichage du timer
  sf::Time timer{sf::Time::Zero};
  int secondes{360};
  sf::Font font;
  sf::Text affichageTimer;


  Troupe *troupeSelectionnee = nullptr;

};

#endif  // BOOK_GAME_HPP
