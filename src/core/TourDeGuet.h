#pragma once
#include "Defense.h"

class TourDeGuet : public Defense {

  private:
  static const int degats = 10;
   sf::Texture texture;
   sf::Sprite sprite;
 public:
  TourDeGuet(float x, float y);
  void attaquer(Troupe* cible) override;
  void draw(sf::RenderWindow& window) const override;
};