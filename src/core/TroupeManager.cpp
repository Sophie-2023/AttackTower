#include "TroupeManager.h"

void TroupeManager::ajouterTroupe(Troupe* troupe) 
{ 
	troupes.push_back(troupe); 
}

void TroupeManager::supprimerTroupe(Troupe* troupe) 
{

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