#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Troupe;

class State {
 public:
  virtual void agir(Troupe& troupe, sf::Time elapsedTime) = 0;
  virtual ~State() {}
};
