#pragma once
#include <vector>
#include "Champ.h"
#include <SFML/Graphics.hpp>
#ifndef CARTE_H
#define CARTE_H

class Carte {
    std::vector<std::unique_ptr<Champ>> champs;
public:
    Carte();
    void update(sf::Time elapsedTime, TroupeManager& TM);
    void draw(sf::RenderWindow& window) const;
};
#endif  // CARTE_H