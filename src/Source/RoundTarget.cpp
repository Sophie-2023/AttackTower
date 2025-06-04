#include "RoundTarget.hpp"
#include <iostream>

RoundTarget::RoundTarget(const float radius, const sf::Color color, float x,
                         float y, float speed_x, float speed_y) {
  mShape.setRadius(radius);
  mShape.setFillColor(color);
  mShape.setPosition({x, y});
  mSpeed = { speed_x, speed_y };
}

sf::CircleShape RoundTarget::getShape() {
    return mShape;
}

void RoundTarget::drawCurrent(sf::RenderWindow &window) const {
  window.draw(mShape);
}

void RoundTarget::handlePlayerInput(const sf::Keyboard::Key &key,
                                    const bool &isPressed) {
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

void RoundTarget::update(const sf::Time &elapsedTime, const sf::Vector2u &windowSize) {


  if (mShape.getPosition().x <= 0 && mSpeed.x < 0) {
      mSpeed.x = -mSpeed.x;
      printf("Left bounce");
  }

  if (mShape.getPosition().y <= 0 && mSpeed.y < 0) {
      mSpeed.y = -mSpeed.y;
      printf("Up bounce");
  }

  if (mShape.getPosition().x >= windowSize.x - 2*mShape.getRadius() && mSpeed.x > 0) {
      mSpeed.x = -mSpeed.x;
      printf("Right bounce");
  }

  if (mShape.getPosition().y >= windowSize.y - 2 * mShape.getRadius() && mSpeed.y > 0) {
      mSpeed.y = -mSpeed.y;
      printf("Bottom bounce");
  }

  sf::Vector2f movement{ mSpeed.x, mSpeed.y };

  if (mIsMovingUp)
    movement.y -= TargetSpeed;
  if (mIsMovingDown)
    movement.y += TargetSpeed;
  if (mIsMovingLeft)
    movement.x -= TargetSpeed;
  if (mIsMovingRight)
    movement.x += TargetSpeed;


  mShape.move(movement * elapsedTime.asSeconds());
}
