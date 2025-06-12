
#include "EtatCombat.h"
#include "Lieu.h"
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
    if (!troupe.getLieuActuel()->getDefenses().empty()) {
      cible = troupe.getLieuActuel()->getDefenses().front().get();
      std::cout << "Cible trouvée" << std::endl;
    }
  } else {
    //sf::Vector2f currentPos = troupe.getPosition();
    //sf::Vector2f targetPos = cible->getPosition();
    //sf::Vector2f delta = targetPos - currentPos;
    //float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    //sf::Vector2f direction = delta.normalized() * troupe.getVitesse();
    //troupe.getSprite().move(direction * elapsedTime.asSeconds());
    //troupe.setPosition(currentPos + direction * elapsedTime.asSeconds());
  }
}