#include "Troupe.h"

Troupe::Troupe(int pv_, float vitesse_)
    : pv(pv_), vitesse(vitesse_) {}

void Troupe::recevoirDegats(int amount) {
  pv += amount;
  if (pv <= 0) pv = 0;
}

int Troupe::random_nMin_to_nMax(int const nMin, int const nMax) {
  static std::random_device rd;
  static std::default_random_engine engine(rd());
  std::uniform_int_distribution distribution(nMin, nMax);
  return distribution(engine);
}