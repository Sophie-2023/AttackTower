#pragma once
#include <SFML/Graphics.hpp>
#include "Defense.h"
#include "Lieu.h"


class Champ : public Lieu {
  int taille;
  int vie;

  sf::Texture texture;
  sf::Sprite sprite;

  std::vector<std::unique_ptr<Defense>> defenses;

 public:
  Champ(const pugi::xml_node& node);
  void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
  void addDefense(const std::string& type, float posx, float posy);
  // void takeDamage(int d);
  sf::FloatRect getBounds() const override;
};