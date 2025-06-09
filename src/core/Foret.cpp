#include "Foret.h"

Foret::Foret(const pugi::xml_node& node)
    : Lieu(node),
      taille(node.attribute("taille").as_int()),
      texture("res/foret.png"),
      sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.01f * taille, 0.01f * taille});
  sprite.setPosition(position);
}

void Foret::update(sf::Time elapsedTime, TroupeManager& TM) {
  // No specific update logic for Foret
}

void Foret::draw(sf::RenderWindow& window) const {
  window.draw(sprite); }

sf::FloatRect Foret::getBounds() const { return sprite.getGlobalBounds(); }

void Foret::rotateTo(const Lieu* target) {
  sf::Vector2f delta = target->getPosition() - position;
  float angleDeg = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;
  sprite.setRotation(sf::degrees(angleDeg));
}