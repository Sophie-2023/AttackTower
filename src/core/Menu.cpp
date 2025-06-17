#include "Menu.h"

const sf::Time Menu::TimePerFrame = sf::seconds(1.f / 60.f);

Menu::Menu(sf::RenderWindow& window)
    : mWindow(window),
      font("res/Bobatime.ttf"), backgroundTexture("res/menu.png"),
      buttonText(font) {
  background.setSize(sf::Vector2f(1280, 720));
  background.setTexture(&backgroundTexture);
  button.setPosition(sf::Vector2f(1110, 630));
  button.setSize(sf::Vector2f(100, 80));
  buttonText.setPosition(sf::Vector2f(1120, 640));
  buttonText.setCharacterSize(50);
  buttonText.setString("Play");
  buttonText.setFillColor(sf::Color::Black);
}

void Menu::render() const {
  mWindow.clear();
  mWindow.draw(background);
  mWindow.draw(button);
  mWindow.draw(buttonText);
  mWindow.display();
}

int Menu::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      if (processEvents()) {
        return 1;
      }
    }
    render();
  }
  return (-1);  // Game closed without victory or defeat
}

bool Menu::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
      sf::Vector2f souris =
          mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
      if (button.getGlobalBounds().contains(souris)) {
        return true;
      }
    } else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }

  return false;
}