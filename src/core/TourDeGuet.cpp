#include "TourDeGuet.h"

TourDeGuet::TourDeGuet(float x, float y)
    : Defense(200, 5, sf::Vector2f(x, y)),
      texture("res/tourDeGuet.png"),
      sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.2f, 0.2f});
  sprite.setPosition(position);
}

  void TourDeGuet::attaquer(Troupe* cible) {
  cible->recevoirDegats(degats);  // La tour de guet inflige 1 point de d�g�ts � la troupe cibl�e
}

void TourDeGuet::draw(sf::RenderWindow& window) const {
    // Dessine la tour de guet
  sf::CircleShape std(
      200);  // Cr�e un cercle de rayon 50 pour repr�senter la zone d'attaque
  std.setPosition(sf::Vector2f(position.x - 200, position.y - 200));
  window.draw(std);
  window.draw(sprite);
};