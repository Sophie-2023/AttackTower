#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>
#include "EtatExploitation.h"
#include <iostream>


Chasseur::Chasseur(Lieu* lieu) 
	: Troupe(50, 50.f),
      texture("res/chasseur.png"),
      sprite(texture)  // pv = 50; vitesse = 50
{ 
    lieuActuel = lieu;
	position = lieuActuel->getPosition();
    decalagePosition = {10.f, -40.f};  // Décalage pour le sprite
    position.x += decalagePosition.x;
    position.y += decalagePosition.y;
    sprite.setOrigin(sprite.getLocalBounds().getCenter() + sf::Vector2f(0, 130));
	sprite.setScale({0.175f, 0.175f});
    sprite.setPosition(position);
}

void Chasseur::draw(sf::RenderWindow& window) const { 
  window.draw(sprite);
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

void Chasseur::update(sf::Time elapsedTime) 
{ 
	sf::Vector2f movement(-vitesse, 0.f);
	//sprite.move(movement * elapsedTime.asSeconds());
    if (etat) {
        etat->agir(*this, elapsedTime);
    }
}