#include "Champ.h"


Champ::Champ(int t, int v, float x, float y)
    : taille(t), vie(v), texture("res/champBle.jpg"), sprite(texture) {
  sprite.setOrigin( sprite.getLocalBounds().getCenter());
  sprite.setScale({0.01f*taille, 0.01f*taille});
  sprite.setPosition(sf::Vector2f(x,y));
}
  
void Champ::draw(sf::RenderWindow& window) const { 
  window.draw(sprite);
  for (auto& defense : defenses) {
    defense->draw(window);
  }
  }


void Champ::update(float dt) {};

void Champ::addDefense(std::unique_ptr<Defense> defense) {
  defenses.push_back(std::move(defense));
}

//void takeDamage(int d);