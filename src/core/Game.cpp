#include "Game.h"
#include <iostream>
#include <EtatEnRoute.h>
#include <memory>


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);



Game::Game() {
  pugi::xml_document doc;
  if (auto result = doc.load_file("res/map.xml"); !result) {
    std::cerr << "Could not open file visage.xml because "
              << result.description() << std::endl;
  }
  pugi::xml_node nodeSource = doc.child("map");
  carte.makeCarte(nodeSource);
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

    if (event->is<sf::Event::MouseButtonPressed>()) {
      
      sf::Vector2f souris = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
      //std::cout << "Souris : (" << souris.x << ", " << souris.y << ")" << std::endl;
      const auto& troupes = troupeManager.getTroupes();

      for (auto troupePtr = troupes.rbegin(); troupePtr != troupes.rend(); ++troupePtr) {
        if ((*troupePtr)->getBounds().contains(souris)) {
          if (troupeSelectionnee) troupeSelectionnee->setSelected(false);
          troupeSelectionnee = troupePtr->get();
          troupeSelectionnee->setSelected(true);
          return;
        }
      }

      if (troupeSelectionnee) {
        for (auto& lieu : carte.getLieux()) {
          if (lieu->getBounds().contains(souris)) {
            std::unique_ptr<EtatEnRoute> etatEnRoute = std::make_unique<EtatEnRoute>();
            etatEnRoute->setDestination(lieu.get());
            troupeSelectionnee->changerEtat(std::move(etatEnRoute));
            troupeSelectionnee->setSelected(false);
            troupeSelectionnee = nullptr;
            return;
          }
        }
      }
    }

    else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}

void Game::update(sf::Time elapsedTime) {
  carte.update(elapsedTime, troupeManager);
  troupeManager.update(elapsedTime);

}

void Game::render() {
  mWindow.clear();
  carte.draw(mWindow);
  troupeManager.draw(mWindow);

  mWindow.display();
}

void Game::handlePlayerInput(const sf::Keyboard::Key key,
                             const bool isPressed) {

}