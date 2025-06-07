#include "Lieu.h"

Lieu::Lieu(const pugi::xml_node& node) :
  position(sf::Vector2f(node.attribute("x").as_int(),node.attribute("y").as_int())) {}

sf::Vector2f Lieu::getPosition() const { return position; }
