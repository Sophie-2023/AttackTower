#include "CanonABle.h"

#include <iostream>

CanonABle::CanonABle(float x, float y)
    : Defense(150, 10, sf::Vector2f(x, y),80),
      texture("res/canon.png"),
      sprite(texture),
      bulletTexture("res/bouletBle.png"),
      bullet(bulletTexture),
      effetExplosionTexture("res/explosion.png")
{
  sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().getCenter().x,sprite.getLocalBounds().size.y));
  sprite.setScale({0.13f, 0.13f});
  sprite.setPosition(position);
  effetExplosion.setTexture(&effetExplosionTexture);
  effetExplosion.setRadius(rayonDegat);
  effetExplosion.setOrigin(effetExplosion.getLocalBounds().getCenter());

  barrePv.setPosition({position.x, position.y - 55.f});
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
  if (pv <= 0) return;
  window.draw(sprite);
  window.draw(barrePv);
  if (attaqueEnCours) {
    window.draw(bullet);
  }
  if (explosionEnCours) {
    window.draw(effetExplosion);
  }
};

void CanonABle::updateAttaque(sf::Time elapsedTime, TroupeManager& TM) {
  if (explosionEnCours) {
    timeExplosion += elapsedTime.asSeconds();
    if (timeExplosion > 0.5f) {
      explosionEnCours = false;
    }
  }
  if (attaqueEnCours) {


    progress += speed * elapsedTime.asSeconds();

    if (progress > 1.0f) progress = 1.0f;

    sf::Vector2f pos = position + (bulletDestination - position) * progress;
    float height = arcHeight * 4 * progress * (1 - progress);
    pos.y -= height;

    bullet.setPosition(pos);
    
    if ((bullet.getPosition() - bulletDestination).length() < 3) {
      effetExplosion.setPosition(bulletDestination);

      for (auto const& cible : TM.getTroupes()) {
        if ((cible->getPosition()-bulletDestination).length() < rayonDegat) {
          cible->recevoirDegats(degats);
        }
      }
      attaqueEnCours = false;
      explosionEnCours  = true;
      progress = 0.f;  
      timeExplosion = 0.f;
    }
  }
}