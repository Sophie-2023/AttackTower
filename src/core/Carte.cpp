#include "Carte.h"
#include "TourDeGuet.h"
Carte::Carte() {
  // Initialize the map with some default values or load from a file
  champs.push_back(std::make_unique<Champ>(10, 100, 50, 50));
  champs.push_back(std::make_unique<Champ>(35, 200, 500, 350));
  std::unique_ptr<Defense> tour = std::make_unique<TourDeGuet>( 100, 100);
  champs[0]->addDefense(std::move(tour));
}

void Carte::update(float dt) {
  for (auto& champ : champs) {
    champ->update(dt);
  }
}

void Carte::draw(sf::RenderWindow& window) const {
  for (auto& champ : champs) {
    champ->draw(window);
  }
}