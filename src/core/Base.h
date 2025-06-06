#pragma once
#include "Lieu.h"

class Base : public Lieu{

  
  sf::Texture texture;
  sf::Sprite sprite;

  public:
  Base(float x, float y);
   void update(sf::Time elapsedTime, TroupeManager& TM) override;
  void draw(sf::RenderWindow& window) const override;
   sf::FloatRect getBounds() const override;
};