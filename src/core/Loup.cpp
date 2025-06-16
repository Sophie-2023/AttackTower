#include <SFML/Graphics.hpp>

#include "Loup.h"
#include <iostream>
#include "EtatExploitation.h"
#include "Defense.h"

Loup::Loup(Lieu* lieu) 
    : Troupe(100, 100, 100.0f, 10, 30.f, sf::seconds(2.f)),  // pv, pvMax, vitesse, degats, rayonDegats, rechargeCombat
      texture("res/loup.png"),
      sprite(texture),
      effetDegatTexture("res/degat.png"),
      effetDegat(effetDegatTexture) 
{ 
  lieuActuel = lieu;
  decalagePosition = {65.f, 0.f};
  position = lieuActuel->getPosition();
  position.x += decalagePosition.x;
  sprite.setOrigin(sprite.getLocalBounds().getCenter() + sf::Vector2f(0, 130));
  sprite.setScale({0.06f, 0.06f});
  sprite.setPosition(position);
  barrePv.setPosition({position.x, position.y - 35.f});
  effetDegat.setOrigin(effetDegat.getLocalBounds().getCenter());
  effetDegat.setScale({0.05f, 0.05f});
}

void Loup::draw(sf::RenderWindow& window) const {
  if (attaqueEnCours) {
    window.draw(effetDegat);
  }

  window.draw(sprite);
  window.draw(barrePv);

  if (auto* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Loup::getBounds() const { return sprite.getGlobalBounds(); }
sf::Sprite& Loup::getSprite() { return sprite; }

void Loup::flip(sf::Vector2f direction) {
  if (direction.x < 0) {
    sprite.setScale({-std::abs(sprite.getScale().x), sprite.getScale().y});
  } else if (direction.x > 0) {
    sprite.setScale({std::abs(sprite.getScale().x), sprite.getScale().y});
  }
}

void Loup::setSelected(bool newBool) {
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Loup::attaquer(Defense* cible) {
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
    std::cout << "Loup attaque défense" << std::endl;
    cible->recevoirDegats(-degats);
  } else {
    lieuActuel->recevoirDegats(-degats);
  }
  attaqueChamp = false;
}

void Loup::updateAttaque(sf::Time elapsedTime) {

  if (attaqueEnCours) {
    tempsEffet += elapsedTime;
    if (tempsEffet >= dureeEffet) {
      attaqueEnCours = false;
    }
  }
}

void Loup::update(sf::Time elapsedTime) {
    barrePv.setPosition({position.x, position.y - 35.f});
    if (etat) {
      etat->agir(*this, elapsedTime);
    }
    updateAttaque(elapsedTime);

}