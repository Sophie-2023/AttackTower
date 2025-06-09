#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class TroupeManager;
class Troupe;

class State {
 protected:
  TroupeManager* troupeManager;
  sf::RenderWindow* window;

 public:
  State(TroupeManager* troupeManager, sf::RenderWindow* window)
      : troupeManager(troupeManager), window(window) {}
  //sf::RenderWindow* getWindow() const { return window; }
  //TroupeManager* getTroupeManager() const { return troupeManager; }
  virtual void agir(Troupe& troupe, sf::Time elapsedTime) = 0;
  virtual ~State() {}
};
