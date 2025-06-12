#pragma once
#include <SFML/Graphics.hpp>
#include "Lieu.h"
#include "Soldat.h"


class Champ : public Lieu {
  int taille;
  int vie;

  sf::Texture texture;
  sf::Sprite sprite;

  Base* base;
  float timeSinceLastSpawn=0;
  float spawnInterval = 15.0f;  // Intervalle de spawn en secondes
  bool underAttack = false;

 public:
  Champ(const pugi::xml_node& node, Base* b);
  void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
  void addDefense(const std::string& type, float posx, float posy);
  std::unique_ptr<Defense> removeSoldat(Defense* soldat);
  // void takeDamage(int d);
  sf::FloatRect getBounds() const override;
  void addSoldat();
  bool getUnderAttack();
};