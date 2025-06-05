#include "TourDeGuet.h"

TourDeGuet::TourDeGuet(float x, float y)
    : Defense(5, 2, sf::Vector2f(x, y)),
      texture("res/tourDeGuet.png"),
      sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.2f, 0.2f});
  sprite.setPosition(position);
}

  void TourDeGuet::attaquer(Troupe* cible) {
  cible->recevoirDegats(degats);  // La tour de guet inflige 1 point de dégâts à la troupe ciblée
}

void TourDeGuet::draw(sf::RenderWindow& window) const {
  window.draw(sprite);  // Dessine la tour de guet
}