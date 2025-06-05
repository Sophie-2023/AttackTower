#include "Carte.h"

Carte::Carte() {
  // Initialize the map with some default values or load from a file
  champs.emplace_back(100,100, 50, 50);
  champs.emplace_back(200,200, 200, 300);
};

void Carte::update(float dt) {
  for (auto& champ : champs) {
    champ.update(dt);
  }
};

void Carte::draw(sf::RenderWindow& window) const {
  for (const auto& champ : champs) {
    champ.draw(window);
  }
};