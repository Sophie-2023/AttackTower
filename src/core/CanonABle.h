#pragma once
#include <SFML/Graphics.hpp>
#include "Defense.h"


class CanonABle : public Defense {
 private:
  static const int degats = -8;
  static const int rayonDegat = 40;
  sf::Texture texture;
  sf::Sprite sprite;


  bool explosionEnCours = false;

  float progress = 0.0f;
  float speed = 1.4f; 
  float arcHeight = 50;
  float timeExplosion = 0.0f;

  sf::Texture bulletTexture;
  sf::Sprite bullet;
  sf::Vector2f bulletDestination;

  sf::Texture effetExplosionTexture;
  sf::CircleShape effetExplosion;

  
  float bulletSpeed = 200;  // Vitesse de la balle

 public:
  CanonABle(float x, float y);
  void attaquer(Troupe* cible) override;
  void draw(sf::RenderWindow& window) const override;
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
};