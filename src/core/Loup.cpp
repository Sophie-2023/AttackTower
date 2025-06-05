#include <SFML/Graphics.hpp>

#include "Loup.h"
#include <iostream>

Loup::Loup() 
    : Troupe(100, 100.0f), texture("res/loup.png"), sprite(texture) {
  position = {static_cast<float>(random_nMin_to_nMax(100, 900)),
              static_cast<float>(random_nMin_to_nMax(100, 600))};
  sprite.setScale({0.1f, 0.1f});
  sprite.setPosition(position);
}

void Loup::draw(sf::RenderWindow& window) const {
  window.draw(sprite);
}

void Loup::update(sf::Time elapsedTime) { 
    sf::Vector2f movement(vitesse, 0.f);
    sprite.move(movement * elapsedTime.asSeconds());
}