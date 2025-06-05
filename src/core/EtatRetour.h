#pragma once

#include "State.h"
#include "Troupe.h"

class EtatRetour : public State {
 public:
  void agir(Troupe& troupe, sf::Time elapsedTime) override;
};