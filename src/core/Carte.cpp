#include "Carte.h"
#include <iostream>
#include "Game.h"




void Carte::makeCarte(const pugi::xml_node& node,Game* gameManager_) {
  gameManager = gameManager_;
  for (pugi::xml_node base1 : node.children("base")) {
    auto base_ = std::make_unique<Base>(base1,this);
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
  bool win = true;
  for (auto const& lieu : lieux) {
    lieu->update(elapsedTime,  TM);
    if (dynamic_cast<Champ*>(lieu.get()) && lieu->isAlive()) {
      win = false;
    }
  }

  if (win) {
    End(win);
  std::cout << "Vous avez gagné !" << std::endl;
  }
  

  // On regarde si une des defenses est détruite pour l'enlever de la liste des lieux
  for (auto const& lieu : lieux) {
    for (auto it = lieu->getDefenses().begin(); it != lieu->getDefenses().end();) {
      if (*it && (*it)->getPv() <= 0) {
        std::cout << "Defense supprimée" << std::endl;
        // Libère la mémoire et enlève du vecteur
        it = lieu->getDefenses().erase(it);
      } else {
        ++it;  // Passe à la suivante
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

void Carte::End(bool win) { gameManager->setEnd(win); };