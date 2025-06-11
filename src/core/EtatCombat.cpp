
#include "EtatCombat.h"
#include <iostream>

EtatCombat::EtatCombat(TroupeManager* tm, sf::RenderWindow* win)
    : State(tm, win) 
{
  cible = nullptr;
}

void EtatCombat::agir(Troupe& troupe, sf::Time elapsedTime) {
  //std::cout << "Je suis au combat" << std::endl;
  if (!cible) {
    //std::cout << "Je cherche une cible" << std::endl;
  }
}