#pragma once

#include "State.h"
#include "Troupe.h"
#include "Defense.h"

class EtatCombat : public State {

  Defense* cible;
  sf::Time tempsEcoule = sf::Time::Zero; // Temps �coul� depuis la derni�re attaque

 public:
  EtatCombat(TroupeManager* tm, sf::RenderWindow* win);
  void agir(Troupe& troupe, sf::Time elapsedTime) override;
};