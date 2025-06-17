#pragma once
#include <SFML/Graphics.hpp>

class Menu {
  sf::RenderWindow& mWindow;

  sf::Font font;

  sf::Texture backgroundTexture;
  sf::RectangleShape background;

  sf::RectangleShape button;
  sf::Text buttonText;

  static const sf::Time TimePerFrame;

 public:
  explicit Menu(sf::RenderWindow& window);
  void render() const;
  bool processEvents();
  int run();
};