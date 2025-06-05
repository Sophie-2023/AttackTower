#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>


Chasseur::Chasseur() 
	: Troupe(50, 50.f),
      texture("res/chasseur.png"),
      sprite(texture)  // pv = 50; vitesse = 50
{ 
	position = {static_cast<float>(random_nMin_to_nMax(100, 900)),
              static_cast<float>(random_nMin_to_nMax(100, 600))};
	sprite.setScale({0.3f, 0.3f});
    sprite.setPosition(position);
}

void Chasseur::draw(sf::RenderWindow& window) const { window.draw(sprite); }

void Chasseur::update(sf::Time elapsedTime) 
{ 
	sf::Vector2f movement(-vitesse, 0.f);
	sprite.move(movement * elapsedTime.asSeconds());
}