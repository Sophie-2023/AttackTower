#pragma once
#include <SFML/Graphics.hpp>

#include "Troupe.h"

class Loup : public Troupe {
 public:
  Loup();
  void draw(sf::RenderWindow& window) const override;
  void update(sf::Time elapsedTime) override;

 private:
  sf::Texture texture;
  sf::Sprite sprite;

};
