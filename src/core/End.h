#pragma once
#include <SFML/Graphics.hpp>

class End {
  sf::RenderWindow& mWindow;

  sf::Font font;
  sf::Text text;

  sf::Texture backgroundTexture;
  sf::RectangleShape background;

  sf::RectangleShape button;
  sf::Text buttonText;

  static const sf::Time TimePerFrame;

 public:
  explicit End(sf::RenderWindow& window);
  void render() const;
  bool processEvents();
  void setWin(bool win);
  int run();
};