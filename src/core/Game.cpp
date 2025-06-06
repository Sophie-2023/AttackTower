#include "Game.h"
#include <iostream>
#include <EtatEnRoute.h>
#include <memory>


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);



Game::Game() {
  // Juste pour tester (à enlever si jamais)
  auto chasseur1 = troupeFactory.creerTroupe("chasseur");
  auto chasseur2 = troupeFactory.creerTroupe("chasseur");
  auto loup = troupeFactory.creerTroupe("loup");
  troupeManager.ajouterTroupe(std::move(chasseur1));
  troupeManager.ajouterTroupe(std::move(chasseur2));
  troupeManager.ajouterTroupe(std::move(loup));
  
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

      for (auto const& troupePtr : troupeManager.getTroupes()) {
        if (troupePtr->getBounds().contains(souris)) {
          if (troupeSelectionnee) troupeSelectionnee->setSelected(false);
          troupeSelectionnee = troupePtr.get();
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