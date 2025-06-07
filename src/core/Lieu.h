#pragma once
#include <SFML/graphics.hpp>
#include "TroupeManager.h"
#include "pugixml.hpp"

class Lieu {


   protected:
  sf::Vector2f position;

  public:
  explicit Lieu(const pugi::xml_node& node);
  virtual void draw(sf::RenderWindow& window) const = 0;
  virtual void update(sf::Time elapsedTime, TroupeManager& TM) = 0;

  virtual sf::FloatRect getBounds() const = 0;
  sf::Vector2f getPosition() const;


};