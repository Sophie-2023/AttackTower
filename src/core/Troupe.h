#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "State.h"

class Carte;  // Forward declaration to avoid circular dependency

class Troupe {

protected:
	int pv;
	float vitesse;
    std::unique_ptr<State> etat;
    sf::Vector2f position;
    bool selected; // Est ce que la troupe est sélectionnée par le joueur ?
    bool isInBase;


public:
    Troupe(int pv_, float vitesse_);
	virtual ~Troupe() = default;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    void recevoirDegats(int amount);
    void changerEtat(std::unique_ptr<State> nouvelEtat);

    sf::Vector2f getPosition() const;
    float getVitesse() const;
    State* getEtat() const;
    bool getIsInBase() const;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Sprite& getSprite() = 0;
    virtual void setSelected(bool newBool);
    void setPosition(sf::Vector2f newPos) { position = newPos; }
    void setIsInBase(bool newBool);

    int random_nMin_to_nMax(int const nMin, int const nMax); // à enlever (c'est ici juste pour tester)

};

