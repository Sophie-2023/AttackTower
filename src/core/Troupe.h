#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "State.h"

class Carte;  // Forward declaration to avoid circular dependency
class Lieu;   // Forward declaration to avoid circular dependency
class Defense;  // Forward declaration to avoid circular dependency

class Troupe {

protected:
	int pv;
    int pvMax;                   
    sf::RectangleShape barrePv;  // Barre de vie pour l'affichage
	float vitesse;
    std::unique_ptr<State> etat;
    sf::Vector2f position;

    int degats;         // Dégâts infligés par la troupe
    float rayonDegats;    // Rayon de la troupe pour les attaques
    sf::Time rechargeCombat;  // Temps de recharge entre les attaques

    bool selected; // Est ce que la troupe est sélectionnée par le joueur ?
    bool isInBase;
    sf::Vector2f decalagePosition;  // Décalage de la position pour le sprite
                                    // (quand il est dans la base, par exemple)
    Lieu* lieuActuel = nullptr;

public:
    Troupe(int pv_, int pvMax_, float vitesse_, int degats_, float rayonDegats_, sf::Time rechargeCombat_);
	virtual ~Troupe() = default;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void attaquer(Defense* cible) = 0;
    virtual void updateAttaque(sf::Time elapsedTime) = 0;
    void recevoirDegats(int amount);
    void changerEtat(std::unique_ptr<State> nouvelEtat);

    sf::Vector2f getPosition() const;
    sf::Vector2f getDecalagePosition() const { return decalagePosition; }
    Lieu* getLieuActuel() const { return lieuActuel; }
    float getVitesse() const;
    int getPv() const { return pv; }    
    State* getEtat() const;
    bool getIsInBase() const;
    int getDegats() const { return degats; }
    float getRayonDegats() const { return rayonDegats; }
    sf::Time getRechargeCombat() const { return rechargeCombat; }
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Sprite& getSprite() = 0;

    virtual void setSelected(bool newBool);
    void setPosition(sf::Vector2f newPos) { position = newPos; }
    void setIsInBase(bool newBool);
    void setLieuActuel(Lieu* lieu);

  
};

