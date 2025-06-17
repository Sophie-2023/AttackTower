#include "EtatEnRoute.h"
#include <iostream>
#include <EtatCombat.h>
#include <Champ.h>
#include <Foret.h>
#include <EtatExploitation.h>

sf::Vector2f normaliser(const sf::Vector2f& v) {
  float longueur = std::sqrt(v.x * v.x + v.y * v.y);
  if (longueur != 0.f)
    return sf::Vector2f(v.x / longueur, v.y / longueur);
  else
    return sf::Vector2f(0.f, 0.f);
}


void EtatEnRoute::agir(Troupe& troupe, sf::Time elapsedTime) {
  if (!destination) {
    std::cout << "Destination non définie pour la troupe." << std::endl;
    return;
  }

  sf::Vector2f currentPos = troupe.getPosition();
  sf::Vector2f targetPos;

  if (phase == 1) targetPos = troupe.getLieuActuel()->getPosition();
  if (phase == 2) targetPos = destination->getPosition();
  if (phase == 3) targetPos = destination->getPosition() + troupe.getDecalagePosition();

  sf::Vector2f delta = targetPos - currentPos;
  float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

  if (distance < 2.f) {

    if (!(phase == 3)) {
      phase++;  // On incrémente le numéro de phase
      return;
    } else {
      troupe.setLieuActuel(destination);
    }

    if (auto const* champ = dynamic_cast<Champ*>(destination)) {
      troupe.changerEtat(std::make_unique<EtatCombat>(troupeManager, window));
    } else if (auto const* foret = dynamic_cast<Foret*>(destination)) {
      troupe.changerEtat(std::make_unique<EtatExploitation>(destination, troupeManager, window));
    } else {
      troupe.changerEtat(std::make_unique<EtatCombat>(troupeManager, window));
      troupe.setIsInBase(true);
    }
    return;
  }

  sf::Vector2f direction = normaliser(delta) * troupe.getVitesse();
  troupe.flip(direction);
  troupe.getSprite().move(direction * elapsedTime.asSeconds());
  troupe.setPosition(currentPos + direction * elapsedTime.asSeconds());
}



