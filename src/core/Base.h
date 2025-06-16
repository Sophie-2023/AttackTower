#pragma once
#include "Lieu.h"
#include "Soldat.h"

class Base : public Lieu{

  
  sf::Texture texture;
  sf::Sprite sprite;

  // EtatCombat choisit comme cible la première defense du vecteur defenses (Lieu.h)

  public:
  Base(const pugi::xml_node& node);
   void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
   sf::FloatRect getBounds() const override;
  void addSoldat(std::unique_ptr<Defense> soldat);
   void death() override;
};