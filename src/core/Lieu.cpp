#include "Lieu.h"

Lieu::Lieu(sf::Vector2f pos) :  position(pos) {}

sf::Vector2f Lieu::getPosition() const { return position; }
