#pragma once
#include "Troupe.h"
#include <SFML/Graphics.hpp>

class Chasseur : public Troupe {
 public:
  explicit Chasseur(Lieu* lieu);
  void draw(sf::RenderWindow& window) const override;
  void update(sf::Time elapsedTime) override;
  void attaquer(Defense* cible) override;
  void updateAttaque(sf::Time elapsedTime) override;
  sf::FloatRect getBounds() const override;
  sf::Sprite& getSprite() override;
  void setSelected(bool newBool) override;
  void flip(sf::Vector2f direction) override;

 private:
  sf::Texture texture;
  sf::Sprite sprite;

  sf::Texture bulletTexture;
  sf::Sprite bullet;
  float bulletSpeed = 300;  // Vitesse de la balle
  Defense* cible = nullptr;

};
