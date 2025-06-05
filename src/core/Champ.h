#pragma once
#include <SFML/Graphics.hpp>


class Champ {
  int taille;
  int vie;

  sf::Texture texture;
  sf::Sprite sprite;

 public:
  Champ(int t, int v, float x, float y);
  void update(float dt);
  void draw(sf::RenderWindow& window) const;
  // void takeDamage(int d);
};