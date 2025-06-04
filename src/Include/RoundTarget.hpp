#ifndef SIMPLE_GAME_ROUND_TARGET_H
#define SIMPLE_GAME_ROUND_TARGET_H

#include <SFML/Graphics.hpp>

class RoundTarget {
public:
  RoundTarget(float radius, sf::Color color, float x, float y, float speed_x, float speed_y);
  void drawCurrent(sf::RenderWindow &window) const;
  void handlePlayerInput(const sf::Keyboard::Key &key, const bool &isPressed);
  void update(const sf::Time &elapsedTime, const sf::Vector2u& windowSize);
  sf::CircleShape getShape();

private:

  static constexpr float TargetSpeed{100.f};
  sf::Vector2f mSpeed;
  bool mIsMovingUp{false};
  bool mIsMovingDown{false};
  bool mIsMovingRight{false};
  bool mIsMovingLeft{false};
  sf::CircleShape mShape;
};

#endif // SIMPLE_GAME_ROUND_TARGET_H
