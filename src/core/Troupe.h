#pragma once
#include <SFML/Graphics.hpp>

class Troupe {

protected:
	int pv;
	float vitesse;
	//State* etat;

public:
    Troupe();
	virtual ~Troupe() = default;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    void recevoirDegats(int amount);
    //void changerEtat(State* nouvelEtat);

    sf::RectangleShape rectangle;

};
