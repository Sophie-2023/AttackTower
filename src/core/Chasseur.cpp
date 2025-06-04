#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>


Chasseur::Chasseur() 
	: Troupe(50, 1.f) 
{ 
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setSize({50.f, 50.f});
    rectangle.setPosition({ static_cast<float>(random_nMin_to_nMax(100, 900)), static_cast<float>(random_nMin_to_nMax(100, 600)) });
}

void Chasseur::draw(sf::RenderWindow& window) const { window.draw(rectangle); }

void Chasseur::update(sf::Time elapsedTime) 
{ 

}