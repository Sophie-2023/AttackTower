#pragma once
#include <SFML/Graphics.hpp>
#include "TroupeManager.h"
#include "Troupe.h"

class Defense {
  float rayon;
  Troupe* cible;
  float timer;
  float cadence;

public:
  sf::Vector2f position;
 
public:
  Defense(float r, float c, sf::Vector2f pos);
  void update(sf::Time elapsedTime, TroupeManager& TM);
  virtual void draw(sf::RenderWindow& window) const = 0;
  virtual void attaquer(Troupe* cible) = 0;
};
