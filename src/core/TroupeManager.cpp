#include "TroupeManager.h"

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