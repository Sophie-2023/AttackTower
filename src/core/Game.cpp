#include "Game.h"
#include <iostream>
#include <EtatEnRoute.h>
#include <memory>
#include "Base.h"


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);



Game::Game(sf::RenderWindow& window) : mWindow(window),font("res/Bobatime.ttf"),affichageTimer(font) {
  pugi::xml_document doc;
  if (auto result = doc.load_file("res/map.xml"); !result) {
    std::cerr << "Could not open file visage.xml because "
              << result.description() << std::endl;
  }
  pugi::xml_node nodeSource = doc.child("map");
  carte.makeCarte(nodeSource,this);
  affichageTimer.setPosition(sf::Vector2f(1200, 10));
  affichageTimer.setString(std::to_string(secondes));
  affichageTimer.setCharacterSize(35);
  affichageTimer.setFillColor(sf::Color::White);

  troupeManager.setCarte(&carte);
  troupeManager.setGameManager(this);
  troupeManager.initializeTroupe(mWindow);
}

int Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen()) {
    if (end) {
      if (win) {
      
      return 1;  // Victory
      } else {
        return 0;  // Defeat
      }
    }
      sf::Time elapsedTime = clock.restart();
      timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
          timeSinceLastUpdate -= TimePerFrame;

          processEvents();
          update(TimePerFrame);
        }
        render();
  }
  return (-1);  // Game closed without victory or defeat
}

void Game::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
      sf::Vector2f souris = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
      const auto& troupes = troupeManager.getTroupes();

      for (auto troupePtr = troupes.rbegin(); troupePtr != troupes.rend();
           ++troupePtr) {
        if ((*troupePtr)->getBounds().contains(souris)) {
          if (troupeSelectionnee) troupeSelectionnee->setSelected(false);
          troupeSelectionnee = troupePtr->get();
          troupeSelectionnee->setSelected(true);
          return;
        }
      }

      if (troupeSelectionnee) {
        for (auto const& lieu : carte.getLieux()) {
          if (lieu->getBounds().contains(souris)) {
            auto const* base = dynamic_cast<Base*>(lieu.get());
            if (base || troupeSelectionnee
                            ->getIsInBase()) {  // Si on clique sur une base ou
                                                // si la troupe est � la base

              auto etatEnRoute = std::make_unique<EtatEnRoute>(lieu.get(), &troupeManager, &mWindow);
              troupeSelectionnee->changerEtat(std::move(etatEnRoute));
              troupeSelectionnee->setIsInBase(false);
              troupeSelectionnee->setSelected(false);
              troupeSelectionnee = nullptr;
              return;
            }
          }
        }
      }
    } else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}

void Game::update(sf::Time elapsedTime) {
  carte.update(elapsedTime, troupeManager);
  troupeManager.update(elapsedTime);
  updateTimer(elapsedTime);

}

void Game::render() {
  mWindow.clear();
  carte.draw(mWindow);
  troupeManager.draw(mWindow);
  mWindow.draw(affichageTimer);
  mWindow.display();
}


void Game::updateTimer(sf::Time elapsedTime) {
  timer += elapsedTime;
  if (timer >= sf::seconds(1.f)) {
    timer -= sf::seconds(1.f);
    --secondes;
  }
  int minutes = secondes / 60;
  int sec_ =secondes% 60;
  if (secondes < 0) {
    secondes = 0;
    setEnd(false);
  }
  affichageTimer.setString(std::to_string(minutes) + ":" + std::to_string(sec_));


}


void Game::setEnd(bool win_) { 
  end = true;
  win = win_;
  }