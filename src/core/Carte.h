#pragma once
#include <vector>
#include "Champ.h"
#include "Base.h"
#include <SFML/Graphics.hpp>
#ifndef CARTE_H
#define CARTE_H

class Carte {
    std::vector<std::unique_ptr<Lieu>> lieux;
public:
    Carte();
    void update(sf::Time elapsedTime, TroupeManager& TM);
    void draw(sf::RenderWindow& window) const;
    std::vector<std::unique_ptr<Lieu>>& getLieux() { return lieux; }
};
#endif  // CARTE_H