#pragma once

#include "State.h"
#include "Troupe.h"
#include "Lieu.h"

class EtatEnRoute : public State {
 private: 
  Lieu* destination;
  TroupeManager* troupeManager;
  sf::RenderWindow* window;
 public:
  EtatEnRoute(Lieu* dest, TroupeManager* tm, sf::RenderWindow* win)
      : destination(dest), troupeManager(tm), window(win) {}
  void agir(Troupe& troupe, sf::Time elapsedTime) override;
  void setDestination(Lieu* dest) { destination = dest; }
};