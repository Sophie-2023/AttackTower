#include "Troupe.h"
#include <iostream>


Troupe::Troupe(int pv_, float vitesse_)
    : pv(pv_),
    vitesse(vitesse_),
    position({0.f, 0.f}),
    selected(false),
    isInBase(true)
{}

void Troupe::recevoirDegats(int amount) {
  pv += amount;
  std::cout << "PV: " << pv << std::endl;
  if (pv <= 0) pv = 0;
}

int Troupe::random_nMin_to_nMax(int const nMin, int const nMax) {
  static std::random_device rd;
  static std::default_random_engine engine(rd());
  std::uniform_int_distribution distribution(nMin, nMax);
  return distribution(engine);
}

sf::Vector2f Troupe::getPosition() const { return position; }
float Troupe::getVitesse() const { return vitesse; }
State* Troupe::getEtat() const { return etat.get(); }
bool Troupe::getIsInBase() const { return isInBase; }


void Troupe::setSelected(bool newBool) { selected = newBool; }
void Troupe::setIsInBase(bool newBool) {
  isInBase = newBool;
}


void Troupe::changerEtat(std::unique_ptr<State> nouvelEtat) {
  etat = std::move(nouvelEtat);
}