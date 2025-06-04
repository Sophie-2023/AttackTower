#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>

int random_nMin_to_nMax(int const nMin, int const nMax) {
  static std::random_device rd;
  static std::default_random_engine engine(rd());
  std::uniform_int_distribution distribution(nMin, nMax);
  return distribution(engine);
}

Chasseur::Chasseur() { 
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setSize({50.f, 50.f});
    rectangle.setPosition({ static_cast<float>(random_nMin_to_nMax(100, 900)), static_cast<float>(random_nMin_to_nMax(100, 600)) });
}

void Chasseur::draw(sf::RenderWindow& window) const { window.draw(rectangle); }

void Chasseur::update(sf::Time elapsedTime) 
{ 

}