#include "Lieu.h"

Lieu::Lieu(sf::Vector2f pos) : voisin(nullptr), position(pos) {}

Lieu* Lieu::getVoisin() const { return voisin; }
sf::Vector2f Lieu::getPosition() const { return position; }

void Lieu::setVoisin(Lieu* v) { 
  this->voisin = v;
  if (voisin->getVoisin() == nullptr) {
    voisin->setVoisin(this);
  }
}