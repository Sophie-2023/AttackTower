#include "Carte.h"
#include "TourDeGuet.h"


Carte::Carte() {
  // Initialize the map with some default values or load from a file
  lieux.push_back(std::make_unique<Base>(500, 350));

  auto champ = std::make_unique<Champ>(10, 100, 200, 200);
  champ->addDefense("tour", 50, 50);
  lieux.push_back(std::move(champ));

  auto champ2 = std::make_unique<Champ>(10, 100, 500, 500);
  champ2->addDefense("canon", -20, 50);
  lieux.push_back(std::move(champ2));



}

void Carte::update(sf::Time elapsedTime, TroupeManager& TM) {
  for (auto& lieu : lieux) {
    lieu->update(elapsedTime,  TM);
  }
}

void Carte::draw(sf::RenderWindow& window) const {
  for (auto& lieu : lieux) {
    lieu->draw(window);
  }
}