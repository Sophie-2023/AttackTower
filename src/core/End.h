#pragma once
#include <SFML/Graphics.hpp>

class End {
  sf::Font font;
  sf::Text text;

  sf::Texture backgroundTexture;
  sf::RectangleShape background;

  sf::RectangleShape button;
  sf::Text buttonText;

 public:
  explicit End();
  void draw(sf::RenderWindow& window) const;
  void setWin(bool win);
};