#include "Carte.h"
#include <iostream>




void Carte::makeCarte(const pugi::xml_node& node) {
  for (pugi::xml_node base1 : node.children("base")) {
    auto base_ = std::make_unique<Base>(base1);
    base = base_.get();
    lieux.push_back(std::move(base_));
  }
  for (pugi::xml_node champ : node.children("champ")) {
    auto champ1 = std::make_unique<Champ>(champ,base);
    chemins.push_back(champ1->createChemin(base));
    lieux.push_back(std::move(champ1));
  }
  for (pugi::xml_node foret : node.children("foret")) {
    auto foret1 = std::make_unique<Foret>(foret);
    foret1->rotateTo(base);
    chemins.push_back(foret1->createChemin(base));
    lieux.push_back(std::move(foret1));
  }
}

void Carte::update(sf::Time elapsedTime, TroupeManager& TM) {
  for (auto& lieu : lieux) {
    lieu->update(elapsedTime,  TM);
  }

  // On regarde si une des defenses est d�truite pour l'enlever de la liste des lieux
  for (auto& lieu : lieux) {
    for (auto it = lieu->getDefenses().begin(); it != lieu->getDefenses().end();) {
      if (*it && (*it)->getPv() <= 0) {
        std::cout << "Defense supprim�e" << std::endl;
        // Lib�re la m�moire et enl�ve du vecteur
        it = lieu->getDefenses().erase(it);
      } else {
        ++it;  // Passe � la suivante
      }
    }
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