#pragma once
#include "Lieu.h"
#include "Soldat.h"

class Base : public Lieu{

  
  sf::Texture texture;
  sf::Sprite sprite;

  std::vector<std::unique_ptr<Soldat>> soldats;

  public:
  Base(const pugi::xml_node& node);
   void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
   sf::FloatRect getBounds() const override;
  void addSoldat(std::unique_ptr<Soldat> soldat);
};