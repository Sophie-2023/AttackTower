#include "Soldat.h"

Soldat::Soldat(sf::Vector2f pos, Lieu* base_)
    : 
  Defense(5, 3, pos),
  pv(40), 
  vitesse(20),
  texture("res/chasseur.png"),
  sprite(texture),
  base(base_){
  sprite.setScale({0.12f, 0.12f});
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setPosition(position);
};

void Soldat::draw(sf::RenderWindow& window) const { window.draw(sprite); }

void Soldat::attaquer(Troupe* cible) {}
void Soldat::updateAttaque(sf::Time elapsedTime, TroupeManager& TM) {
  sf::Vector2f direction =(base->getPosition() - position).normalized() * vitesse;
  position += direction * elapsedTime.asSeconds();
  sprite.move(direction * elapsedTime.asSeconds());
}