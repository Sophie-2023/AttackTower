#include "TourDeGuet.h"
#include <iostream>

TourDeGuet::TourDeGuet(float x, float y)
    : Defense(400, 5, sf::Vector2f(x, y)),
      texture("res/tourDeGuet.png"),
      sprite(texture),
      bulletTexture("res/bullet.png"),
      bullet(bulletTexture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.2f, 0.2f});
  sprite.setPosition(position);
}

  void TourDeGuet::attaquer(Troupe* c) {
  cible = c;
  attaqueEnCours = true;
  std::cout << "attaque de la tour de guet" << std::endl;
  bullet.setPosition(position);
  bullet.setScale(sf::Vector2f(0.01f,0.01f));  // Ajuste la taille de la balle
  bullet.setOrigin(bullet.getLocalBounds().getCenter());

}

void TourDeGuet::draw(sf::RenderWindow& window) const {
    // Dessine la tour de guet
  sf::CircleShape std(
      400);  // Crée un cercle de rayon 50 pour représenter la zone d'attaque
  std.setPosition(sf::Vector2f(position.x - 200, position.y - 200));
  //window.draw(std);
  window.draw(sprite);
  if (attaqueEnCours) {
    window.draw(bullet);  }
  };

void TourDeGuet::updateAttaque(sf::Time elapsedTime) {
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