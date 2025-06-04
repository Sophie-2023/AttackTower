#include "Game.hpp"
#include <random>
#include <string>
#include <cmath>
#include <iostream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

int random_nMin_to_nMax(int const nMin, int const nMax) {
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution distribution(nMin, nMax);
    return distribution(engine);
}

Game::Game() {
  assert(mFont.openFromFile("media/Sansation.ttf"));
  // We do not need to do mStatisticsText.setFont(mFont); as mStatisticsText is
  // initialized with a reference to mFont
  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);
  initializeTargets();
}

void Game::initializeTargets() {
    for (int i = 1; i <= 100; i++) {
        sf::Color color = chooseRandomColor();
        float radius = random_nMin_to_nMax(10, 50);
        float position_x = random_nMin_to_nMax(0, 640 - radius);
        float position_y = random_nMin_to_nMax(0, 480 - radius);
        float speed_x = random_nMin_to_nMax(-100, 100);
        float speed_y = std::sqrt(1000 - speed_x * speed_x);
        RoundTarget target = RoundTarget(radius, color, position_x, position_y, speed_x, speed_y);
        mTargets.push_back(target);

        printf("\n");
        std::cout << i << " : " << speed_x;

    }
}

sf::Color Game::chooseRandomColor() {
    int i = random_nMin_to_nMax(1, 4);

    if (i == 1) return sf::Color::Yellow;
    if (i == 2) return sf::Color::Blue;
    if (i == 3) return sf::Color::Cyan;
    if (i == 4) return sf::Color::Magenta;
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  mWindow.setVerticalSyncEnabled(true);
  while (mWindow.isOpen()) {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processEvents();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = mWindow.pollEvent()) {

    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      mTarget.handlePlayerInput(keyPressed->code, true);
    } 
    
    else if (const auto *keyReleased =
                   event->getIf<sf::Event::KeyReleased>()) {
      mTarget.handlePlayerInput(keyReleased->code, false);
    } 
    
    else if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }
  }
}

void Game::update(const sf::Time elapsedTime) { 
    mTarget.update(elapsedTime, mWindow.getSize());
    
    for (auto& target : mTargets) {
        target.update(elapsedTime, mWindow.getSize());
    }

}

void Game::render() {
  mWindow.clear();
  mTarget.drawCurrent(mWindow);

  for (auto target : mTargets) {
      target.drawCurrent(mWindow);
  }

  mWindow.draw(mStatisticsText);
  mWindow.display();
}

void Game::updateStatistics(const sf::Time elapsedTime) {
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;

  if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
    mStatisticsText.setString(std::format(
        "Frames / Second = {}\nTime / Update = {} us", mStatisticsNumFrames,
        mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames));

    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
}