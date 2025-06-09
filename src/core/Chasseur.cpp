#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>
#include "EtatExploitation.h"


Chasseur::Chasseur() 
	: Troupe(50, 50.f),
      texture("res/chasseur.png"),
      sprite(texture)  // pv = 50; vitesse = 50
{ 
	position = {500.f, 350.f};
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
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