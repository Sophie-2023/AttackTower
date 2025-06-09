#pragma once
#include <vector>
#include <memory>
#include "Troupe.h"
#include "TroupeFactory.h"

class Carte;

class TroupeManager {
 private:
  std::vector<std::unique_ptr<Troupe>> troupes;
  TroupeFactory troupeFactory;

 public:
  TroupeManager();
  void ajouterTroupe(std::unique_ptr<Troupe> troupe);
  void supprimerTroupe(std::unique_ptr<Troupe> troupe);
  void update(sf::Time elapsedTime);
  void draw(sf::RenderWindow& window);
  std::vector<std::unique_ptr<Troupe>>& getTroupes() { return troupes; }
  void setCarte(Carte* carte);

};
