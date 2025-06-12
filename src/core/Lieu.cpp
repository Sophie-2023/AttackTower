#include "Lieu.h"
#include <iostream>

Lieu::Lieu(const pugi::xml_node& node)
    : textureChemin("res/chemin.jpg"),
      pvMax(node.attribute("vie").as_int()),
      position(sf::Vector2f(node.attribute("x").as_int(),
                            node.attribute("y").as_int()))
{
  pv = pvMax;  // Initialiser les points de vie
  textureChemin.setRepeated(true);
}

sf::Vector2f Lieu::getPosition() const { return position; }

std::unique_ptr<sf::RectangleShape> Lieu::createChemin(Lieu* destination) const {
  float distance = std::sqrt((destination->getPosition().x - position.x) * (destination->getPosition().x - position.x) +
                             (destination->getPosition().y - position.y) * (destination->getPosition().y - position.y));

  // Fonction pour calculer l'angle entre deux points en degrés
  float angleDeg = std::atan2(destination->getPosition().y - position.y,
                              destination->getPosition().x - position.x) * 180.f / 3.14159265f;

    float largeur = 50;  // largeur du chemin


    std::unique_ptr<sf::RectangleShape> chemin = std::make_unique<sf::RectangleShape>();
    chemin->setSize(sf::Vector2f(distance, largeur));
    chemin->setTexture(&textureChemin);
    chemin->setOrigin(sf::Vector2f(0.f, largeur / 2.f));
    // Positionner le rectangle au point A
    chemin->setPosition(position);

    // Appliquer la rotation vers le point B
    chemin->setRotation(sf::degrees(angleDeg));
    return (std::move(chemin));
  }
void Lieu::recevoirDegats(int amount) {
  pv += amount;
  if (pv <= 0) pv = 0;
  if (pv > pvMax) pv = pvMax;

  float proportion = static_cast<float>(pv) / static_cast<float>(pvMax);
  proportion = std::clamp(proportion, 0.f, 1.f);  // éviter valeur négative
  std::cout << "Points de vie: " << pv  << std::endl;
  //barrePv.setSize({50.f * proportion, 5.f});
}