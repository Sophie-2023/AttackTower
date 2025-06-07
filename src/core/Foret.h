#pragma once
#include "Lieu.h"
class Foret : public Lieu {
  int taille;  // Taille de la foret

  sf::Texture texture;
  sf::Sprite sprite;


 public:
  Foret(const pugi::xml_node& node);
  void draw(sf::RenderWindow& window) const override;
  void update(sf::Time elapsedTime, TroupeManager& TM) override;

 sf::FloatRect getBounds() const override;
};