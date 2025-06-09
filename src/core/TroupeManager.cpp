#include "TroupeManager.h"
#include "TroupeFactory.h"
#include "Carte.h"

TroupeManager::TroupeManager() {

}

void TroupeManager::initializeTroupe() {
  auto chasseur1 = creerTroupe("chasseur", carte->getBase());
  auto chasseur2 = creerTroupe("chasseur", carte->getBase());
  auto loup = creerTroupe("loup", carte->getBase());
  ajouterTroupe(std::move(chasseur1));
  ajouterTroupe(std::move(chasseur2));
  ajouterTroupe(std::move(loup));
}

void TroupeManager::setCarte(Carte* carte_) { carte = carte_; }

std::unique_ptr<Troupe> TroupeManager::creerTroupe(const std::string& type, Lieu* lieu) {
  return troupeFactory.creerTroupe(type, lieu->getPosition());
}

void TroupeManager::ajouterTroupe(std::unique_ptr<Troupe> troupe) {
  troupesEnAttente.push_back(std::move(troupe));
}

void TroupeManager::supprimerTroupe(std::unique_ptr<Troupe> troupe) {

}

void TroupeManager::draw(sf::RenderWindow& window) { 
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
    for (auto& newTroupe : troupesEnAttente) {
        troupes.push_back(std::move(newTroupe));
    }
    troupesEnAttente.clear();
}