#pragma once
#include <SFML/graphics.hpp>
#include "TroupeManager.h"

class Lieu {

  Lieu* voisin;

   protected:
  sf::Vector2f position;

  public:
  explicit Lieu(sf::Vector2f pos);
  Lieu* getVoisin() const;
  void setVoisin(Lieu* v);
  virtual void draw(sf::RenderWindow& window) const = 0;
  virtual void update(sf::Time elapsedTime, TroupeManager& TM) = 0;


};