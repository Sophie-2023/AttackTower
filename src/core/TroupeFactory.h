#pragma once
#include "Troupe.h"
#include <memory>

class TroupeFactory {
 public:
  std::unique_ptr<Troupe> creerTroupe(const std::string& type, sf::Vector2f pos);

};
