#pragma once
#include <SFML/Graphics.hpp>
#include "Defense.h"


class Champ {
  int taille;
  int vie;

  sf::Texture texture;
  sf::Sprite sprite;

  std::vector<std::unique_ptr<Defense>> defenses;

 public:
  Champ(int t, int v, float x, float y);
  void update(sf::Time elapsedTime, TroupeManager& TM);
  void draw(sf::RenderWindow& window) const;
  void addDefense(const std::string& nom, float posx, float posy);
  // void takeDamage(int d);
};