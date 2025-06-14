#pragma once
#include "Defense.h"
class Base;

class Champ;

class Soldat : public Defense {
 private:
  int pv; // Il y a d�j� pv dans Defense ! A enlever quand on initialisera les pv des d�fenses de fa�on plus propre
  float vitesse;
  sf::Texture texture;
  sf::Sprite sprite;
  Base* base;  // Base o� va le soldat
  
  float time = 0.f;
  Champ* proprio;
  int degats = -5;
  Troupe* cible = nullptr;

  bool enMarche = false;
  bool attaqueBase = false;

 public:
  Soldat(sf::Vector2f pos, Base* base, Champ* p);
  void draw(sf::RenderWindow& window) const override;
  void attaquer(Troupe* cible) override;
  void attaquerBase();
  void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) override;
};