#include "Champ.h"


Champ::Champ(int t, int v, float x, float y)
    : taille(t), vie(v), texture("res/champBle.jpg"), sprite(texture) {
  sprite.setScale({0.01f*taille, 0.01f*taille});
  sprite.setPosition(sf::Vector2f(x,y));
}
  
void Champ::draw(sf::RenderWindow& window) const { window.draw(sprite); }


void Champ::update(float dt) {};

//void takeDamage(int d);