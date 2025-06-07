#include "Carte.h"
#include <iostream>




void Carte::makeCarte(const pugi::xml_node& node) {
  for (pugi::xml_node base1 : node.children("base")) {
    auto base_ = std::make_unique<Base>(base1);
    base = base_.get();
    lieux.push_back(std::move(base_));
  }
  for (pugi::xml_node champ : node.children("champ")) {
    auto champ1 = std::make_unique<Champ>(champ);
    chemins.push_back(champ1->createChemin(base));
    lieux.push_back(std::move(champ1));
  }
  for (pugi::xml_node foret : node.children("foret")) {
    auto foret1 = std::make_unique<Foret>(foret);
    chemins.push_back(foret1->createChemin(base));
    lieux.push_back(std::move(foret1));
  }
}

void Carte::update(sf::Time elapsedTime, TroupeManager& TM) {
  for (auto& lieu : lieux) {
    lieu->update(elapsedTime,  TM);
  }
}

void Carte::draw(sf::RenderWindow& window) const {
  for (auto& chemin : chemins) {
    window.draw(*chemin);
  }
  for (auto& lieu : lieux) {
    lieu->draw(window);
  }
}