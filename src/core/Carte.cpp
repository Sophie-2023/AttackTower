#include "Carte.h"
#include "TourDeGuet.h"
Carte::Carte() {
  // Initialize the map with some default values or load from a file
  champs.push_back(std::make_unique<Champ>(10, 100, 200, 200));
  //champs.push_back(std::make_unique<Champ>(35, 200, 500, 350));
  champs[0]->addDefense( "tour", 50, 50);
}

void Carte::update(sf::Time elapsedTime, TroupeManager& TM) {
  for (auto& champ : champs) {
    champ->update(elapsedTime,  TM);
  }
}

void Carte::draw(sf::RenderWindow& window) const {
  for (auto& champ : champs) {
    champ->draw(window);
  }
}