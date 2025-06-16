#include "TourDeGuet.h"
#include <iostream>

TourDeGuet::TourDeGuet(float x, float y)
    : Defense(200, 5, sf::Vector2f(x, y),100),
      texture("res/tourDeGuet.png"),
      sprite(texture),
      bulletTexture("res/bullet.png"),
      bullet(bulletTexture) {
  sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().getCenter().x,sprite.getLocalBounds().size.y));
  sprite.setScale({0.15f, 0.15f});
  sprite.setPosition(position);
  barrePv.setPosition({position.x, position.y - 75.f});
}

  #include <SFML/System/Angle.hpp> // Include necessary header for sf::Angle

  void TourDeGuet::attaquer(Troupe* c) {
    cible = c;
    attaqueEnCours = true;
    std::cout << "attaque de la tour de guet" << std::endl;
    bullet.setPosition(position);
    bullet.setScale(sf::Vector2f(0.01f, 0.01f));  // Ajuste la taille de la balle
    bullet.setOrigin(bullet.getLocalBounds().getCenter());
    
    // Convert float to sf::Angle using sf::radians
    sf::Angle rotationAngle = sf::radians(
        std::atan2(cible->getPosition().y - position.y,
                   cible->getPosition().x - position.x));
    
    bullet.setRotation(rotationAngle);  // Définit la rotation de la balle vers la cible
  }

void TourDeGuet::draw(sf::RenderWindow& window) const {
    // Dessine la tour de guet
  sf::CircleShape std(
      400);  // Crée un cercle de rayon 50 pour représenter la zone d'attaque
  std.setPosition(sf::Vector2f(position.x - 200, position.y - 200));
  //window.draw(std);
  window.draw(sprite);
  window.draw(barrePv);
  if (attaqueEnCours) {
    window.draw(bullet);  }
  };

void TourDeGuet::updateAttaque(sf::Time elapsedTime, TroupeManager& TM) {
  if (attaqueEnCours) {
     sf::Vector2f direction =
        (cible->getPosition() - bullet.getPosition()).normalized() * bulletSpeed;
    bullet.move(direction * elapsedTime.asSeconds() ); 
    if ((bullet.getPosition() - cible->getPosition()).length()<3) {
      cible->recevoirDegats(degats); 
      attaqueEnCours=false;  
    }
  }
}