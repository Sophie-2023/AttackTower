#pragma once
#include <SFML/graphics.hpp>
#include "TroupeManager.h"
#include "Defense.h"
#include "pugixml.hpp"

class Lieu {
 private:
  sf::Texture textureChemin;
  int pvMax;
  int pv;
   protected:
  sf::Vector2f position;
  std::vector<std::unique_ptr<Defense>> defenses;

  public:
  explicit Lieu(const pugi::xml_node& node);
  virtual void draw(sf::RenderWindow& window) const = 0;
  virtual void update(sf::Time elapsedTime, TroupeManager& TM) = 0;

  virtual sf::FloatRect getBounds() const = 0;
  sf::Vector2f getPosition() const;
  std::vector<std::unique_ptr<Defense>>& getDefenses() { return defenses; }
  std::unique_ptr<sf::RectangleShape> createChemin(Lieu* destination) const;
  void recevoirDegats(int amount);


};