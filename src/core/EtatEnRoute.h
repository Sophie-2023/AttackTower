#pragma once

#include "State.h"
#include "Troupe.h"
#include "Lieu.h"

class EtatEnRoute : public State {
 private: 
  Lieu* destination;
  int phase = 1;

 public:
  EtatEnRoute(Lieu* dest, TroupeManager* tm, sf::RenderWindow* win)
      : State(tm, win), destination(dest) {}
  void agir(Troupe& troupe, sf::Time elapsedTime) override;
  void setDestination(Lieu* dest) { destination = dest; }
};