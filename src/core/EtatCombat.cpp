
#include "EtatCombat.h"
#include "Lieu.h"
#include "Champ.h"
#include <iostream>

EtatCombat::EtatCombat(TroupeManager* tm, sf::RenderWindow* win)
    : State(tm, win) 
{
  cibleDefense = nullptr;
}

void EtatCombat::agir(Troupe& troupe, sf::Time elapsedTime) {

  if (!cibleDefense || cibleDefense->getPv() <= 0) {

    auto* lieu = troupe.getLieuActuel();
    if (!lieu->getDefenses().empty()) {
      cibleDefense = lieu->getDefenses().front().get();
      ciblePosition = cibleDefense->getPosition();
      troupe.setAttaqueChamp(false);  // on attaque une défense
    } else if (Champ const* champ = dynamic_cast<Champ*>(lieu)) {
      if (champ->isAlive()) {
        troupe.setAttaqueChamp(true);  // on cible le champ
        ciblePosition = champ->getPosition();
        cibleDefense = nullptr;
      }
    } else {
      cibleDefense = nullptr;
      troupe.setAttaqueChamp(false);  // rien à faire
    }

  } 
  
  if (cibleDefense || troupe.getAttaqueChamp()) {
    sf::Vector2f currentPos = troupe.getPosition();
    sf::Vector2f delta = ciblePosition - currentPos;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y) - troupe.getRayonDegats();

    if (distance < 2.f) {
      tempsEcoule += elapsedTime;
      if (tempsEcoule >= troupe.getRechargeCombat()) {
        troupe.attaquer(cibleDefense);
        tempsEcoule = sf::Time::Zero;  // Réinitialiser le temps écoulé après l'attaque
        cibleDefense = nullptr;      // La troupe rechoisit sa cible
      }
      return;  // On sort de la fonction pour éviter de bouger la troupe
    } else {
      sf::Vector2f direction = delta.normalized() * troupe.getVitesse();
      troupe.flip(direction);
      troupe.getSprite().move(direction * elapsedTime.asSeconds());
      troupe.setPosition(currentPos + direction * elapsedTime.asSeconds());
    }

  }
}