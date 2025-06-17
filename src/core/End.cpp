#include "End.h"

const sf::Time End::TimePerFrame = sf::seconds(1.f / 60.f);


End::End(sf::RenderWindow& window)
    : mWindow(window) ,font("res/Bobatime.ttf"), text(font), buttonText(font) {
  background.setSize(sf::Vector2f(1280, 720));
  text.setPosition(sf::Vector2f(450, 400));
  text.setCharacterSize(100);
  button.setPosition(sf::Vector2f(450, 600));
  button.setSize(sf::Vector2f(200, 80));
  buttonText.setPosition(sf::Vector2f(460, 610));
  buttonText.setCharacterSize(50);
  buttonText.setString("Replay?");
  buttonText.setFillColor(sf::Color::Black);
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

void End::render() const {
   mWindow.clear();
      mWindow.draw(background);
      mWindow.draw(text);
      mWindow.draw(button);
      mWindow.draw(buttonText);
  mWindow.display();
}

int End::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      if (processEvents()) {
        return 0;
      }
    }
    render();
  }
  return (-1);  // Game closed without victory or defeat
}

bool End::processEvents() {
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