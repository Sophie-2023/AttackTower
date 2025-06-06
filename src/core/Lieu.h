#pragma once
#include <SFML/graphics.hpp>
#include "TroupeManager.h"

class Lieu {


   protected:
  sf::Vector2f position;

  public:
  explicit Lieu(sf::Vector2f pos);
  virtual void draw(sf::RenderWindow& window) const = 0;
  virtual void update(sf::Time elapsedTime, TroupeManager& TM) = 0;

  virtual sf::FloatRect getBounds() const = 0;
  sf::Vector2f getPosition() const;


};