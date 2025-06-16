#include "End.h"

End::End() : font("res/Bobatime.ttf"), text(font) {
  background.setSize(sf::Vector2f(1000, 700));
  text.setPosition(sf::Vector2f(500, 350));
  text.setCharacterSize(100);
}

void End::setWin(bool win) {
  if (win) {
    backgroundTexture.loadFromFile("res/win.png");
    background.setTexture(&backgroundTexture);
    text.setString("You win !");
  } else {
    backgroundTexture.loadFromFile("res/lose.png");
    background.setTexture(&backgroundTexture);
    text.setString("You lose !");
  }

  
 }

void End::draw(sf::RenderWindow& window) const {
  window.draw(background);
  window.draw(text);
}