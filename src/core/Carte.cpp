#include "Carte.h"
#include <iostream>




void Carte::makeCarte(const pugi::xml_node& node) {
  for (pugi::xml_node base : node.children("base")) {
    lieux.push_back(std::make_unique<Base>(base));
  }
  for (pugi::xml_node champ : node.children("champ")) {
    auto champ1 = std::make_unique<Champ>(champ);
    lieux.push_back(std::move(champ1));
  }
  for (pugi::xml_node foret : node.children("foret")) {
    lieux.push_back(std::make_unique<Foret>(foret));
  }
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