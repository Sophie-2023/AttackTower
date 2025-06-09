#pragma once
#include <vector>
#include <memory>
#include "Troupe.h"
#include "TroupeFactory.h"

class Carte;
class Lieu;  // Forward declaration to avoid circular dependency

class TroupeManager {
 private:
  std::vector<std::unique_ptr<Troupe>> troupes;
  std::vector<std::unique_ptr<Troupe>> troupesEnAttente; // Pour éviter d'ajouter une troupe pendant un parcours de troupes
  TroupeFactory troupeFactory;

  Carte* carte = nullptr;  // Pointeur vers la carte associée

 public:
  TroupeManager();
  void initializeTroupe();
  std::unique_ptr<Troupe> creerTroupe(const std::string& type, Lieu* lieu);
  void ajouterTroupe(std::unique_ptr<Troupe> troupe);
  void supprimerTroupe(std::unique_ptr<Troupe> troupe);
  void update(sf::Time elapsedTime);
  void draw(sf::RenderWindow& window);
  std::vector<std::unique_ptr<Troupe>>& getTroupes() { return troupes; }

  Carte* getCarte() const { return carte; } // Pour avoir accès à la base
  void setCarte(Carte* carte);

};
