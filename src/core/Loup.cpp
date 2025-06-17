#include <SFML/Graphics.hpp>

#include "Loup.h"
#include <iostream>
#include "EtatExploitation.h"
#include "Defense.h"
#include "EtatEnRoute.h"

Loup::Loup(Lieu* lieu) 
    : Troupe(40, 40, 100.0f, 10, 30.f, sf::seconds(2.f)),  // pv, pvMax, vitesse, degats, rayonDegats, rechargeCombat
      texture("res/loup0.png"),
      sprite(texture),
      effetDegatTexture("res/degat.png"),
      effetDegat(effetDegatTexture) 
{ 
  texturesCourse.resize(4);
  for (int i = 0; i < 4; ++i) {  
      texturesCourse[i].loadFromFile(std::format("res/loup{}.png", i)); 
      texturesCourse[i].setSmooth(false);
      }
  texturesAttaque.resize(7);
  for (int i = 0; i < 6; ++i) {
    texturesAttaque[i].loadFromFile(std::format("res/loupMorsure{}.png", i));
      texturesAttaque[i].setSmooth(false);
  }
  
  lieuActuel = lieu;
  decalagePosition = {65.f, 0.f};
  position = lieuActuel->getPosition();
  position.x += decalagePosition.x;
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.18f, 0.18f});
  sprite.setPosition(position);
  barrePv.setPosition({position.x, position.y - 35.f});
  effetDegat.setOrigin(effetDegat.getLocalBounds().getCenter());
  effetDegat.setScale({0.05f, 0.05f});
}

void Loup::draw(sf::RenderWindow& window) const {
  if (pv <= 0) return;
  if (attaqueEnCours && tempsEffet.asSeconds() >= 0.18f) {
    window.draw(effetDegat);
  }
  window.draw(sprite);
  window.draw(barrePv);

  if (auto const* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Loup::getBounds() const { return sprite.getGlobalBounds(); }
sf::Sprite& Loup::getSprite() { return sprite; }

void Loup::flip(sf::Vector2f direction) {
  if (direction.x < 0) {
    sprite.setScale({-std::abs(sprite.getScale().x), sprite.getScale().y});
  } else if (direction.x > 0) {
    sprite.setScale({std::abs(sprite.getScale().x), sprite.getScale().y});
  }
}

void Loup::setSelected(bool newBool) {
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Loup::attaquer(Defense* cible) {
  sf::Vector2f ciblePosition;
  if (cible) {
    ciblePosition = cible->getPosition();
  } else {
    ciblePosition = lieuActuel->getPosition();
  }

  effetDegat.setPosition(ciblePosition);
  attaqueEnCours = true;
  textureIndex = 0;
  tempsSprite = sf::Time::Zero;
  tempsEffet = sf::Time::Zero;
  if (cible) {
    cible->recevoirDegats(-degats);
  } else {
    lieuActuel->recevoirDegats(-degats);
  }
  attaqueChamp = false;
}

void Loup::updateAttaque(sf::Time elapsedTime) {

  if (attaqueEnCours) {
    if (tempsSprite.asSeconds() > 0.06f) {
      tempsSprite -= sf::seconds(0.06f);
      sprite.setTexture(texturesAttaque[textureIndex]);
      sprite.setOrigin(sprite.getLocalBounds().getCenter());
      textureIndex = (textureIndex + 1) % 6;
    } else {
      tempsSprite += elapsedTime;
    }
    tempsEffet += elapsedTime;
    if (tempsEffet >= dureeEffet) {
      attaqueEnCours = false;
      textureIndex = 0;
    }
  }
}

void Loup::update(sf::Time elapsedTime) {
    barrePv.setPosition({position.x, position.y - 35.f});
    if (etat) {
      etat->agir(*this, elapsedTime);
    }

    updateAttaque(elapsedTime);
    if (dynamic_cast<EtatEnRoute*>(getEtat())) {
      if (tempsSprite.asSeconds() > 0.1f ) {
        tempsSprite -= sf::seconds(0.1f);
        sprite.setTexture(texturesCourse[textureIndex]);
        sprite.setOrigin(sprite.getLocalBounds().getCenter());
        textureIndex = (textureIndex + 1) % 4;
      } else {
        tempsSprite += elapsedTime;
      }
    }

}