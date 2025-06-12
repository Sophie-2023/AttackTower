#pragma once
#include "Defense.h"
class Base;

class Champ;

class Soldat : public Defense {
 private:
  int pv;
  float vitesse;
  sf::Texture texture;
  sf::Sprite sprite;
  Base* base;  // Base où va le soldat
  bool enMarche = false;
  float time = 0.f;
  Champ* proprio;
  int degats = 3;

 public:
  Soldat(sf::Vector2f pos, Base* base, Champ* p);
  void draw(sf::RenderWindow& window) const override;
  void attaquer(Troupe* cible) override;
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
};