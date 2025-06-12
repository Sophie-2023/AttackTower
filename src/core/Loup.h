#pragma once
#include <SFML/Graphics.hpp>

#include "Troupe.h"

class Loup : public Troupe {
 public:
  explicit Loup(Lieu* lieu);
  void draw(sf::RenderWindow& window) const override;
  void update(sf::Time elapsedTime) override;
  void attaquer(Defense* cible) override;
  void updateAttaque(sf::Time elapsedTime) override;
  sf::FloatRect getBounds() const override;
  sf::Sprite& getSprite() override;
  void setSelected(bool newBool) override;

 private:
  sf::Texture texture;
  sf::Sprite sprite;

};
