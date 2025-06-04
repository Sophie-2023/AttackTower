#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "State.h"

class Troupe {

protected:
	int pv;
	float vitesse;
    std::unique_ptr<State> etat;


public:
    Troupe(int pv_, float vitesse_);
	virtual ~Troupe() = default;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    void recevoirDegats(int amount);
    //void changerEtat(State* nouvelEtat);
    int random_nMin_to_nMax(int const nMin, int const nMax); // à enlever (c'est ici juste pour tester)

};

