#pragma once
#include <vector>
#include "Troupe.h"

class TroupeManager {
 private:
  std::vector<Troupe*> troupes; // à changer avec unique_ptr

 public:
  void ajouterTroupe(Troupe* troupe);
  void supprimerTroupe(Troupe* troupe);
  void update(sf::Time elapsedTime);
  void draw(sf::RenderWindow& window);
};
