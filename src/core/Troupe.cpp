#include "Troupe.h"
#include <iostream>
#include "Lieu.h"


Troupe::Troupe(int pv_, int pvMax_, float vitesse_)
    : pv(pv_),
      pvMax(pvMax_),
      vitesse(vitesse_),
      position({0.f, 0.f}),
      selected(false),
      isInBase(true),
      decalagePosition({0.f, 0.f}) 
{
  barrePv.setSize({50.f, 5.f});
  barrePv.setFillColor(sf::Color::Red);
}

void Troupe::recevoirDegats(int amount) {
  pv += amount;
  if (pv <= 0) pv = 0;
  std::cout << "PV: " << pv << std::endl;

  // Mettre à jour la barre de vie
  float proportion = static_cast<float>(pv) / static_cast<float>(pvMax);
  proportion = std::clamp(proportion, 0.f, 1.f);  // éviter valeur négative

  barrePv.setSize({50.f * proportion, 5.f});
}


sf::Vector2f Troupe::getPosition() const { return position; }
float Troupe::getVitesse() const { return vitesse; }
State* Troupe::getEtat() const { return etat.get(); }
bool Troupe::getIsInBase() const { return isInBase; }


void Troupe::setSelected(bool newBool) { selected = newBool; }
void Troupe::setIsInBase(bool newBool) {
  isInBase = newBool;
}
void Troupe::setLieuActuel(Lieu* lieu) { lieuActuel = lieu; }


void Troupe::changerEtat(std::unique_ptr<State> nouvelEtat) {
  etat = std::move(nouvelEtat);
}