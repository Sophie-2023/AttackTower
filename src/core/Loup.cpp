#include <SFML/Graphics.hpp>

#include "Loup.h"
#include <iostream>

Loup::Loup() 
    : Troupe(100, 100.0f), texture("res/loup.png"), sprite(texture) {
  position = {static_cast<float>(random_nMin_to_nMax(100, 900)),
              static_cast<float>(random_nMin_to_nMax(100, 600))};
  sprite.setScale({0.06f, 0.06f});
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setPosition(position);
}

void Loup::draw(sf::RenderWindow& window) const {
  window.draw(sprite);
}

sf::FloatRect Loup::getBounds() const { return sprite.getGlobalBounds(); }

void Loup::setSelected(bool newBool) {
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Loup::update(sf::Time elapsedTime) { 
    sf::Vector2f movement(vitesse, 0.f);
    //sprite.move(movement * elapsedTime.asSeconds());
    if (etat) {
      etat->agir(*this, elapsedTime);
    }
}