#include "TroupeFactory.h"
#include "Chasseur.h"
#include "Loup.h"
#include "Elephant.h"
#include <iostream>


std::unique_ptr<Troupe> TroupeFactory::creerTroupe(const std::string& type, Lieu* lieu) {
  if (type == "loup") {
    return std::make_unique<Loup>(lieu);
  }
  if (type == "elephant") return std::make_unique<Elephant>(lieu);
  if (type == "chasseur") return std::make_unique<Chasseur>(lieu);
  return nullptr;
}
