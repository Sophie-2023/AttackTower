#pragma once
#include "Defense.h"
#include "Lieu.h"
class Soldat : public Defense {
 private:
  int pv;
  float vitesse;
  sf::Texture texture;
  sf::Sprite sprite;
  Lieu* base;  // Base où va le soldat

 public:
  Soldat(sf::Vector2f pos,Lieu* base);
  void draw(sf::RenderWindow& window) const override;
  void attaquer(Troupe* cible) override;
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
};