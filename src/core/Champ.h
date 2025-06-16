#pragma once
#include <SFML/Graphics.hpp>
#include "Lieu.h"
#include "Soldat.h"
#include "TroupeManager.h"


class Champ : public Lieu {
  int taille;

  sf::Texture texture;
  sf::Sprite sprite;

  Base* base;
  float timeSinceLastSpawn=0;
  float spawnInterval = 15.0f;  // Intervalle de spawn en secondes
  bool underAttack = false;
  TroupeManager* troupeManager = nullptr;

  std::vector<std::unique_ptr<Defense>> soldatsEnRoute;

 public:
  Champ(const pugi::xml_node& node, Base* b);
  void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
  void addDefense(const std::string& type, float posx, float posy);

  // s'occuper des soldats pour qu'ils aillent vers la base ennemie
  std::unique_ptr<Defense> removeSoldatEnRoute(Defense* soldat);
  // void takeDamage(int d);
  sf::FloatRect getBounds() const override;
  void addSoldat();
  void moveToSoldatEnRoute(const Defense* soldat);
  bool getUnderAttack();
  void death() override;
};