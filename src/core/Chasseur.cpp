#include "Chasseur.h"
#include <SFML/Graphics.hpp>

#include <random>
#include "EtatExploitation.h"
#include <iostream>
#include "Defense.h"


Chasseur::Chasseur(Lieu* lieu) 
	: Troupe(50, 50, 50.f, 10, 70.f, sf::seconds(2.f)),  // pv, pvMax, vitesse, degats, rayonDegats, rechargeCombat
      texture("res/chasseur.png"),
      sprite(texture),
      bulletTexture("res/bullet.png"),
      bullet(bulletTexture)
{ 
    lieuActuel = lieu;
	position = lieuActuel->getPosition();
    decalagePosition = {10.f, -40.f};  // Décalage pour le sprite
    position.x += decalagePosition.x;
    position.y += decalagePosition.y;
    sprite.setOrigin(sprite.getLocalBounds().getCenter() + sf::Vector2f(0, 130));
	sprite.setScale({0.175f, 0.175f});
    sprite.setPosition(position);
    barrePv.setPosition({position.x, position.y - 60.f});
}

void Chasseur::draw(sf::RenderWindow& window) const { 
  window.draw(sprite);
  window.draw(barrePv);
  if (attaqueEnCours) {
    window.draw(bullet);
  }

  if (auto* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Chasseur::getBounds() const {
	return sprite.getGlobalBounds();
}

sf::Sprite& Chasseur::getSprite() { return sprite; }

void Chasseur::flip(sf::Vector2f direction) {
  if (direction.x < 0) {
    sprite.setScale({-std::abs(sprite.getScale().x), sprite.getScale().y});
  } else if (direction.x > 0) {
    sprite.setScale({std::abs(sprite.getScale().x), sprite.getScale().y});
  }
}

void Chasseur::setSelected(bool newBool) { 
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Chasseur::attaquer(Defense* cible_) {
  cible = cible_;
  attaqueEnCours = true;
  std::cout << "attaque du chasseur" << std::endl;
  bullet.setPosition(position);
  bullet.setScale(sf::Vector2f(0.01f, 0.01f));  // Ajuste la taille de la balle
  bullet.setOrigin(bullet.getLocalBounds().getCenter());
  bullet.setColor(sf::Color::Blue);

  // Convert float to sf::Angle using sf::radians
  sf::Angle rotationAngle =
      sf::radians(std::atan2(cible->getPosition().y - position.y,
                             cible->getPosition().x - position.x));

  bullet.setRotation(
      rotationAngle);  // Définit la rotation de la balle vers la cible
}

void Chasseur::updateAttaque(sf::Time elapsedTime) {
  if (attaqueEnCours) {
    sf::Vector2f direction =
        (cible->getPosition() - bullet.getPosition()).normalized() *
        bulletSpeed;
    bullet.move(direction * elapsedTime.asSeconds());
    if ((bullet.getPosition() - cible->getPosition()).length() < 3) {
      if (cible) {
        cible->recevoirDegats(-degats);
        //std::cout << "Chasseur attaque la cible, PV restants: "
        //          << cible->getPv() << std::endl;
      }
      attaqueEnCours = false;
      cible = nullptr;
    }
  }
}

void Chasseur::update(sf::Time elapsedTime) 
{ 
    barrePv.setPosition({position.x, position.y - 60.f});
    if (etat) {
        etat->agir(*this, elapsedTime);
    }
    updateAttaque(elapsedTime);
}