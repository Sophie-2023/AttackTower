#include "Game.hpp"
#include "StringHelpers.hpp"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() {
  mTarget.setRadius(50.f);
  mTarget.setFillColor(sf::Color::Cyan);
  mTarget.setPosition({100.f, 100.f});

  assert(mFont.openFromFile("media/Sansation.ttf"));
  // We do not need to do mStatisticsText.setFont(mFont); as mStatisticsText is
  // initialized with a reference to mFont
  mStatisticsText.setPosition({5.f, 5.f});
  mStatisticsText.setCharacterSize(10);
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

    updateStatistics(elapsedTime);
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
  sf::Vector2f movement(0.f, 0.f);
  if (mIsMovingUp)
    movement.y -= PlayerSpeed;
  if (mIsMovingDown)
    movement.y += PlayerSpeed;
  if (mIsMovingLeft)
    movement.x -= PlayerSpeed;
  if (mIsMovingRight)
    movement.x += PlayerSpeed;

  mTarget.move(movement * elapsedTime.asSeconds());
}

void Game::render() {
  mWindow.clear();
  mWindow.draw(mTarget);
  mWindow.draw(mStatisticsText);
  mWindow.display();
}

void Game::updateStatistics(const sf::Time elapsedTime) {
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;

  if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
    mStatisticsText.setString(
        "Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
        "Time / Update = " +
        toString(mStatisticsUpdateTime.asMicroseconds() /
                 mStatisticsNumFrames) +
        " us");

    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
}

void Game::handlePlayerInput(const sf::Keyboard::Key key,
                             const bool isPressed) {
  using enum sf::Keyboard::Key;
  if (key == Z)
    mIsMovingUp = isPressed;
  else if (key == S)
    mIsMovingDown = isPressed;
  else if (key == Q)
    mIsMovingLeft = isPressed;
  else if (key == D)
    mIsMovingRight = isPressed;
}
