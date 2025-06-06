#include "CanonABle.h"

#include <iostream>

CanonABle::CanonABle(float x, float y)
    : Defense(400, 10, sf::Vector2f(x, y)),
      texture("res/canon.png"),
      sprite(texture),
      bulletTexture("res/bouletBle.png"),
      bullet(bulletTexture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.1f, 0.1f});
  sprite.setPosition(position);
}


void CanonABle::attaquer(Troupe* c) {
  bulletDestination = c->getPosition();
  attaqueEnCours = true;
  std::cout << "attaque du canon" << std::endl;
  bullet.setPosition(position);
  bullet.setScale(sf::Vector2f(0.03f, 0.03f));  // Ajuste la taille de la balle
  bullet.setOrigin(bullet.getLocalBounds().getCenter());

}

void CanonABle::draw(sf::RenderWindow& window) const {
  // Dessine la tour de guet
  window.draw(sprite);
  if (attaqueEnCours) {
    window.draw(bullet);
  }
};

void CanonABle::updateAttaque(sf::Time elapsedTime, TroupeManager& TM) {
  if (attaqueEnCours) {
    /* sf::Vector2f direction =
        (bulletDestination - bullet.getPosition()).normalized() *
        bulletSpeed;
    bullet.move(direction * elapsedTime.asSeconds());
    */


    progress += speed * elapsedTime.asSeconds();
    if (progress > 1.0f) progress = 1.0f;

    sf::Vector2f pos = position + (bulletDestination - position) * progress;
    float height = arcHeight * 4 * progress * (1 - progress);
    pos.y -= height;

    bullet.setPosition(pos);
    
    if ((bullet.getPosition() - bulletDestination).length() < 3) {

      for (auto& cible : TM.getTroupes()) {
        if ((cible->getPosition()-bulletDestination).length() < rayonDegat) {
          cible->recevoirDegats(degats);
        }
      }
      attaqueEnCours = false;
      progress = 0.f;  
    }
  }
}