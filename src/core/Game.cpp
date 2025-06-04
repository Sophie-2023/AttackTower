#include "Game.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() {
  Troupe *chasseur = troupeFactory.creerTroupe("chasseur");
  troupeManager.ajouterTroupe(chasseur);
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processEvents();
      update(TimePerFrame);
    }
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      handlePlayerInput(keyPressed->code, true);
    } else if (const auto *keyReleased =
                   event->getIf<sf::Event::KeyReleased>()) {
      handlePlayerInput(keyReleased->code, false);
    } else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}

void Game::update(sf::Time elapsedTime) {
  troupeManager.update(elapsedTime);
}

void Game::render() {
  mWindow.clear();
  troupeManager.draw(mWindow);
  mWindow.display();
}

void Game::handlePlayerInput(const sf::Keyboard::Key key,
                             const bool isPressed) {

}