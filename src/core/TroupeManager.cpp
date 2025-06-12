#include "TroupeManager.h"
#include "TroupeFactory.h"
#include "Carte.h"
#include <iostream>

#include "EtatCombat.h"

void TroupeManager::initializeTroupe(sf::RenderWindow& window) {
  auto chasseur1 = creerTroupe("chasseur", carte->getBase());
  auto chasseur2 = creerTroupe("chasseur", carte->getBase());
  auto loup = creerTroupe("loup", carte->getBase());
  chasseur1->changerEtat(std::make_unique<EtatCombat>(this, &window));
  chasseur2->changerEtat(std::make_unique<EtatCombat>(this, &window));
  loup->changerEtat(std::make_unique<EtatCombat>(this, &window));
  ajouterTroupe(std::move(chasseur1));
  ajouterTroupe(std::move(chasseur2));
  ajouterTroupe(std::move(loup));
}

void TroupeManager::setCarte(Carte* carte_) { carte = carte_; }

std::unique_ptr<Troupe> TroupeManager::creerTroupe(const std::string& type, Lieu* lieu) {
  return troupeFactory.creerTroupe(type, lieu);
}

void TroupeManager::ajouterTroupe(std::unique_ptr<Troupe> troupe) {
  troupesEnAttente.push_back(std::move(troupe));
}

void TroupeManager::supprimerTroupe(std::unique_ptr<Troupe> troupe) {

}

void TroupeManager::draw(sf::RenderWindow& window) const { 
	for (auto const& troupe : troupes) {
		troupe->draw(window);
	}
}

void TroupeManager::update(sf::Time elapsedTime) {
	for (auto const& troupe : troupes) {
		if (troupe) {
		  troupe->update(elapsedTime);
		}
	}

    // On regarde si une des troupes est morte pour l'enlever de la liste des troupes
	for (auto it = troupes.begin(); it != troupes.end(); ) {
        if (*it && (*it)->getPv() <= 0) {
        std::cout << "Troupe supprimée" << std::endl;
        // Libère la mémoire et enlève du vecteur
        it = troupes.erase(it);
        } else {
        ++it;  // Passe à la suivante
        }
    }


    for (auto& newTroupe : troupesEnAttente) {
        troupes.push_back(std::move(newTroupe));
    }
    troupesEnAttente.clear();
}