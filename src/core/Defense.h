#pragma once
#include <SFML/Graphics.hpp>
#include "TroupeManager.h"
#include "Troupe.h"
#include "pugixml.hpp"

class Defense {
 
  float rayon;
  Troupe* cible;
  float timer;
  float cadence;

protected:
  bool attaqueEnCours = false;
  bool underAttack = false;
  int pv;
  int pvMax;
  sf::RectangleShape barrePv;

public:
  sf::Vector2f position;
 
public:
  Defense(float r, float c, sf::Vector2f pos,int pv_);
 virtual ~Defense() = default;
  void update(sf::Time elapsedTime, TroupeManager& TM);
  virtual void draw(sf::RenderWindow& window) const = 0;
  virtual void attaquer(Troupe* cible) = 0;
  virtual void updateAttaque(sf::Time elapsedTime, TroupeManager& TM) = 0;
  void recevoirDegats(int amount);

  int getPv() const { return pv; }
  sf::Vector2f getPosition() const { return position; }
  bool getAttaqueEnCours();

};
