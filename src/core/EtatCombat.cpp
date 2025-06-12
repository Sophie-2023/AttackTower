
#include "EtatCombat.h"
#include "Lieu.h"
#include <iostream>

EtatCombat::EtatCombat(TroupeManager* tm, sf::RenderWindow* win)
    : State(tm, win) 
{
  cible = nullptr;
}

void EtatCombat::agir(Troupe& troupe, sf::Time elapsedTime) {

  if (!cible) {

    if (!troupe.getLieuActuel()->getDefenses().empty()) {
      cible = troupe.getLieuActuel()->getDefenses().front().get();
    }

  } else {
    sf::Vector2f currentPos = troupe.getPosition();
    sf::Vector2f targetPos = cible->getPosition();
    sf::Vector2f delta = targetPos - currentPos;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y) - troupe.getRayonDegats();

    if (distance < 2.f) {
      
      return;  // On sort de la fonction pour éviter de bouger la troupe
    } else {
      sf::Vector2f direction = delta.normalized() * troupe.getVitesse();
      troupe.getSprite().move(direction * elapsedTime.asSeconds());
      troupe.setPosition(currentPos + direction * elapsedTime.asSeconds());
    }

  }
}