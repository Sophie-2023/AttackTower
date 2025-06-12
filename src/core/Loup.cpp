#include <SFML/Graphics.hpp>

#include "Loup.h"
#include <iostream>
#include "EtatExploitation.h"
#include "Defense.h"

Loup::Loup(Lieu* lieu) 
    : Troupe(100, 100, 100.0f, 10, 30.f, sf::seconds(2.f)),  // pv, pvMax, vitesse, degats, rayonDegats, rechargeCombat
      texture("res/loup.png"),
      sprite(texture) { 
  lieuActuel = lieu;
  decalagePosition = {65.f, 0.f};
  position = lieuActuel->getPosition();
  position.x += decalagePosition.x;
  sprite.setOrigin(sprite.getLocalBounds().getCenter() + sf::Vector2f(0, 130));
  sprite.setScale({0.06f, 0.06f});
  sprite.setPosition(position);
  barrePv.setPosition({position.x, position.y - 35.f});
}

void Loup::draw(sf::RenderWindow& window) const {
  window.draw(sprite);
  window.draw(barrePv);

  if (auto* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Loup::getBounds() const { return sprite.getGlobalBounds(); }
sf::Sprite& Loup::getSprite() { return sprite; }

void Loup::setSelected(bool newBool) {
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Loup::attaquer(Defense* cible) {
  if (cible) {
    cible->recevoirDegats(-degats);
    //std::cout << "Loup attaque la defense, PV restants: " << cible->getPv() << std::endl;
  }
}

void Loup::updateAttaque(sf::Time elapsedTime) {
  // Pas d'attaque pour le loup, mais on peut implémenter une logique si
  // nécessaire
}

void Loup::update(sf::Time elapsedTime) {
    barrePv.setPosition({position.x, position.y - 35.f});
    if (etat) {
      etat->agir(*this, elapsedTime);
    }
}