#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>
#include "EtatExploitation.h"
#include <iostream>
#include "Defense.h"


Chasseur::Chasseur(Lieu* lieu) 
	: Troupe(50, 50, 50.f, 10, 70.f, sf::seconds(2.f)),  // pv, pvMax, vitesse, degats, rayonDegats, rechargeCombat
      texture("res/chasseur.png"),
      sprite(texture)
{ 
    lieuActuel = lieu;
	position = lieuActuel->getPosition();
    decalagePosition = {10.f, -40.f};  // Décalage pour le sprite
    position.x += decalagePosition.x;
    position.y += decalagePosition.y;
    sprite.setOrigin(sprite.getLocalBounds().getCenter() + sf::Vector2f(0, 130));
	sprite.setScale({0.175f, 0.175f});
    sprite.setPosition(position);
    barrePv.setPosition({position.x, position.y - 60.f});
}

void Chasseur::draw(sf::RenderWindow& window) const { 
  window.draw(sprite);
  window.draw(barrePv);

  if (auto* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Chasseur::getBounds() const {
	return sprite.getGlobalBounds();
}

sf::Sprite& Chasseur::getSprite() { return sprite; }

void Chasseur::setSelected(bool newBool) { 
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Chasseur::attaquer(Defense* cible) {
  if (cible) {
    cible->recevoirDegats(-degats);
    //std::cout << "Chasseur attaque la defense, PV restants: " << cible->getPv()
    //          << std::endl;
  }
}

void Chasseur::updateAttaque(sf::Time elapsedTime) {
  // Pas d'attaque pour le chasseur, mais on peut implémenter une logique si
  // nécessaire
}

void Chasseur::update(sf::Time elapsedTime) 
{ 
    barrePv.setPosition({position.x, position.y - 60.f});
    if (etat) {
        etat->agir(*this, elapsedTime);
    }
}