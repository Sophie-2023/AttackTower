#pragma once
#include "Defense.h"

class TourDeGuet : public Defense {

  private:
  static const int degats = -15;
   sf::Texture texture;
   sf::Sprite sprite;


   sf::Texture bulletTexture;
   sf::Sprite bullet;
   Troupe* cible = nullptr;

   float bulletSpeed = 300;  // Vitesse de la balle

 public:
  TourDeGuet(float x, float y);
  void attaquer(Troupe* cible) override;
  void draw(sf::RenderWindow& window) const override;
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
};