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
  //std::cout << "Je suis en route" << std::endl;
  if (!destination) {
    std::cout << "Destination non définie pour la troupe." << std::endl;
    return;
  }

  sf::Vector2f position = troupe.getPosition();
  sf::Vector2f delta = destination->getPosition() - position;
  float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

  if (distance < 2.f) {

    if (auto* champ = dynamic_cast<Champ*>(destination)) {
      troupe.changerEtat(std::make_unique<EtatCombat>());
      std::cout << "Arrivée à destination : champ" << std::endl;
    } else if (auto* foret = dynamic_cast<Foret*>(destination)) {
      troupe.changerEtat(std::make_unique<EtatExploitation>());
      std::cout << "Arrivée à destination : foret" << std::endl;
    } else {
      troupe.changerEtat(nullptr);
      std::cout << "Arrivée à destination : base"
                << std::endl;
    }
    return;
  }

  sf::Vector2f direction = normaliser(destination->getPosition() - position) * troupe.getVitesse();
  troupe.getSprite().move(direction * elapsedTime.asSeconds());
  troupe.setPosition(position + direction * elapsedTime.asSeconds());
}
