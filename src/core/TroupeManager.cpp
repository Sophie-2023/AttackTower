#include "TroupeManager.h"
#include "TroupeFactory.h"

TroupeManager::TroupeManager() {

  auto chasseur1 = troupeFactory.creerTroupe("chasseur");
  auto chasseur2 = troupeFactory.creerTroupe("chasseur");
  auto loup = troupeFactory.creerTroupe("loup");
  ajouterTroupe(std::move(chasseur1));
  ajouterTroupe(std::move(chasseur2));
  ajouterTroupe(std::move(loup));

}

void TroupeManager::ajouterTroupe(std::unique_ptr<Troupe> troupe) { 
	troupes.push_back(std::move(troupe)); 
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
    troupe->update(elapsedTime);
	}
};