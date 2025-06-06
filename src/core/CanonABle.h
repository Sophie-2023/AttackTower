#pragma once
#include <SFML/Graphics.hpp>
#include "Defense.h"


class CanonABle : public Defense {
 private:
  static const int degats = -8;
  static const int rayonDegat = 12;
  sf::Texture texture;
  sf::Sprite sprite;

  bool attaqueEnCours = false;

  float progress = 0.0f;
  float speed = 0.8; 
  float arcHeight = 50;

  sf::Texture bulletTexture;
  sf::Sprite bullet;
  sf::Vector2f bulletDestination;

  float bulletSpeed = 200;  // Vitesse de la balle

 public:
  CanonABle(float x, float y);
  void attaquer(Troupe* cible) override;
  void draw(sf::RenderWindow& window) const override;
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
};