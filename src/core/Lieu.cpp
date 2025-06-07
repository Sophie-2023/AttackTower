#include "Lieu.h"

Lieu::Lieu(const pugi::xml_node& node)
    : textureChemin("res/chemin.jpg"),
      position(sf::Vector2f(node.attribute("x").as_int(),
                            node.attribute("y").as_int())) {
  textureChemin.setRepeated(true);
}

sf::Vector2f Lieu::getPosition() const { return position; }

std::unique_ptr<sf::RectangleShape> Lieu::createChemin(Lieu* destination) const {
  float distance = std::sqrt((destination->getPosition().x - position.x) * (destination->getPosition().x - position.x) +
                             (destination->getPosition().y - position.y) * (destination->getPosition().y - position.y));

  // Fonction pour calculer l'angle entre deux points en degrés
  float angleDeg = std::atan2(destination->getPosition().y - position.y,
                              destination->getPosition().x - position.x) * 180.f / 3.14159265f;

    float largeur = 30;  // largeur du chemin


    std::unique_ptr<sf::RectangleShape> chemin = std::make_unique<sf::RectangleShape>();
    chemin->setSize(sf::Vector2f(distance, largeur));
    chemin->setTexture(&textureChemin);

    // Positionner le rectangle au point A
    chemin->setPosition(position);

    // Appliquer la rotation vers le point B
    chemin->setRotation(sf::degrees(angleDeg));
    return (std::move(chemin));
  }