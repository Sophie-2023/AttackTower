#include <SFML/Graphics.hpp>
#include <iostream>

#include "Defense.h"
#include "EtatEnRoute.h"
#include "EtatExploitation.h"
#include "Elephant.h"

Elephant::Elephant(Lieu* lieu)
    : Troupe(
          100, 100, 30.0f, 20, 30.f, sf::seconds(2.f)),  // pv, pvMax, vitesse, degats, rayonDegats, rechargeCombat
      texture("res/elephant.png"),
      sprite(texture),
      effetDegatTexture("res/degat.png"),
      effetDegat(effetDegatTexture) 
{

  lieuActuel = lieu;
  decalagePosition = {-65.f, -10.f};
  position = lieuActuel->getPosition();
  position.x += decalagePosition.x;
  position.y += decalagePosition.y;
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({2.f, 2.f});
  sprite.setPosition(position);
  barrePv.setPosition({position.x, position.y - 35.f});
  effetDegat.setOrigin(effetDegat.getLocalBounds().getCenter());
  effetDegat.setScale({0.05f, 0.05f});
}

void Elephant::draw(sf::RenderWindow& window) const {
  if (pv <= 0) return;
  if (attaqueEnCours && tempsEffet.asSeconds() >= 0.18f) {
    window.draw(effetDegat);
  }
  window.draw(sprite);
  window.draw(barrePv);

  if (auto const* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Elephant::getBounds() const { return sprite.getGlobalBounds(); }
sf::Sprite& Elephant::getSprite() { return sprite; }

void Elephant::flip(sf::Vector2f direction) {
  if (direction.x < 0) {
    sprite.setScale({-std::abs(sprite.getScale().x), sprite.getScale().y});
  } else if (direction.x > 0) {
    sprite.setScale({std::abs(sprite.getScale().x), sprite.getScale().y});
  }
}

void Elephant::setSelected(bool newBool) {
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Elephant::attaquer(Defense* cible) {
  sf::Vector2f ciblePosition;
  if (cible) {
    ciblePosition = cible->getPosition();
  } else {
    ciblePosition = lieuActuel->getPosition();
  }

  effetDegat.setPosition(ciblePosition);
  attaqueEnCours = true;
  tempsEffet = sf::Time::Zero;
  if (cible) {
    cible->recevoirDegats(-degats);
  } else {
    lieuActuel->recevoirDegats(-degats);
  }
  attaqueChamp = false;
}

void Elephant::updateAttaque(sf::Time elapsedTime) {
  if (attaqueEnCours) {
    tempsEffet += elapsedTime;
    if (tempsEffet >= dureeEffet) {
      attaqueEnCours = false;
    }
  }
}

void Elephant::update(sf::Time elapsedTime) {
  barrePv.setPosition({position.x, position.y - 35.f});
  if (etat) {
    etat->agir(*this, elapsedTime);
  }

  updateAttaque(elapsedTime);
}