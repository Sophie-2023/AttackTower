#pragma once
#include "Troupe.h"
#include <SFML/Graphics.hpp>

class Chasseur : public Troupe {
 public:
  Chasseur(sf::Vector2f pos);
  void draw(sf::RenderWindow& window) const override;
  void update(sf::Time elapsedTime) override;
  sf::FloatRect getBounds() const override;
  sf::Sprite& getSprite() override;
  void setSelected(bool newBool) override;

 private:
  sf::Texture texture;
  sf::Sprite sprite;
};
