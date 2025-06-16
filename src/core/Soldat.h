#pragma once
#include "Defense.h"
class Base;

class Champ;

class Soldat : public Defense {
 private:
  float vitesse;
  sf::Texture texture;
  sf::Sprite sprite;
  Base* base;  // Base où va le soldat
  
  float time = 0.f;
  Champ* proprio;
  int degats = -8;
  Troupe* cible = nullptr;

  bool enMarche = false;
  bool attaqueBase = false;
  bool dansEnRoute = false;

 public:
  Soldat(sf::Vector2f pos, Base* base, Champ* p);
  void draw(sf::RenderWindow& window) const override;
  void attaquer(Troupe* cible) override;
  void attaquerBase();
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
  void flip(sf::Vector2f direction);

};