#include "Lieu.h"

Lieu::Lieu(sf::Vector2f pos):position(pos),voisin(nullptr) {}

Lieu* Lieu::getVoisin() const { return voisin; }


void Lieu::setVoisin(Lieu* v) { 
  this->voisin = v;
  if (voisin->getVoisin() == nullptr) {
    voisin->setVoisin(this);
  }
}