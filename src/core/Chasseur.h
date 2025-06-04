#pragma once
#include "Troupe.h"
#include <SFML/Graphics.hpp>

class Chasseur : public Troupe {
 public:
  Chasseur();
  void draw(sf::RenderWindow& window) const override;
  void update(sf::Time elapsedTime) override;

  
};
