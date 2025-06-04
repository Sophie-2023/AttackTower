#include <SFML/Graphics.hpp>

#include "Loup.h"

Loup::Loup() 
    : Troupe(100, 2.0f) {
  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize({50.f, 50.f});
  rectangle.setPosition({static_cast<float>(random_nMin_to_nMax(100, 900)),
                         static_cast<float>(random_nMin_to_nMax(100, 600))});
}

void Loup::draw(sf::RenderWindow& window) const { window.draw(rectangle); }

void Loup::update(sf::Time elapsedTime) {}