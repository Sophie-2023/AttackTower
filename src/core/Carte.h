#pragma once
#include <vector>
#include "Champ.h"
#include <SFML/Graphics.hpp>


class Carte {
  std::vector<Champ> champs;

 public:
  Carte();
  void update(float dt);
  void draw(sf::RenderWindow& window) const;
};