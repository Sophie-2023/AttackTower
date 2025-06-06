#pragma once

#include "State.h"
#include "Troupe.h"
#include "Lieu.h"

class EtatEnRoute : public State {
 private: 
  Lieu* destination;
 public:
  void agir(Troupe& troupe, sf::Time elapsedTime) override;
  void setDestination(Lieu* dest) { destination = dest; }
};