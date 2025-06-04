#pragma once

#include <memory>

class Troupe;

class State {
 public:
  virtual void agir(std::unique_ptr<Troupe> troupe) = 0;
  virtual ~State() {}
};
