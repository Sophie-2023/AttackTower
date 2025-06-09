#pragma once
#include <SFML/Graphics.hpp>
#include "Defense.h"
#include "Lieu.h"
#include "Soldat.h"


class Champ : public Lieu {
  int taille;
  int vie;

  sf::Texture texture;
  sf::Sprite sprite;

  Lieu* base;

  std::vector<std::unique_ptr<Defense>> defenses;
  std::vector<std::unique_ptr<Soldat>> soldats;

 public:
  Champ(const pugi::xml_node& node, Lieu* b);
  void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
  void addDefense(const std::string& type, float posx, float posy);
  // void takeDamage(int d);
  sf::FloatRect getBounds() const override;
};