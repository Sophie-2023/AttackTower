#pragma once
#include <vector>
#include "Champ.h"
#include "Base.h"
#include <SFML/Graphics.hpp>
#include "pugixml.hpp"
#include "Foret.h"
#ifndef CARTE_H
#define CARTE_H

class Carte {
  std::vector<std::unique_ptr<Lieu>> lieux;
  Base* base=nullptr;
  std::vector<std::unique_ptr<sf::RectangleShape>> chemins;

 public:
    Carte()=default;
    void makeCarte(const pugi::xml_node& node);
    void update(sf::Time elapsedTime, TroupeManager& TM);
    void draw(sf::RenderWindow& window) const;
    std::vector<std::unique_ptr<Lieu>>& getLieux() { return lieux; }
    Base* getBase() const { return base; }
};
#endif  // CARTE_H