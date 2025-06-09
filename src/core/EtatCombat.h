#pragma once

#include "State.h"
#include "Troupe.h"

class EtatCombat : public State {
 public:
  EtatCombat(TroupeManager* tm, sf::RenderWindow* win) : State(tm, win) {}
  void agir(Troupe& troupe, sf::Time elapsedTime) override;
};