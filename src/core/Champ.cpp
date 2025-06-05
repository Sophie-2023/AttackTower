#include "Champ.h"


Champ::Champ(int t, int v, float x, float y)
    : taille(t), vie(v) {
  texture.loadFromFile("res/champBle.jpg");
  sprite.setTexture(texture);
  sprite.setScale({0.3f, 0.3f});
  sprite.setPosition(x, y);
}
  
void Champ::draw(sf::RenderWindow& window) { window.draw(sprite); }


void Champ::update(float dt) {};

//void takeDamage(int d);