#include "Base.h"
#include <iostream>

Base::Base(const pugi::xml_node& node)
    : Lieu(node), texture("res/base.png"), sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.5f, 0.5f});
  sprite.setPosition(position);
  barrePv.setFillColor(sf::Color::White);
  barrePv.setSize({80, 5.f});
  prop = sf::Vector2f(80, 5.f);
  barrePv.setOrigin(barrePv.getLocalBounds().getCenter());
  barrePv.setPosition(sf::Vector2f(
      position.x, position.y - sprite.getGlobalBounds().size.y / 2 ));
}

void Base::update(sf::Time elapsedTime, TroupeManager& TM) {
  for (auto& soldat : defenses) {
    soldat->update(elapsedTime, TM);
  }
}

void Base::draw(sf::RenderWindow& window) const {
  window.draw(sprite);
  for (auto& soldat : defenses) {
    if (soldat) {
      soldat->draw(window);
    }
  }
  window.draw(barrePv);
}

sf::FloatRect Base::getBounds() const { return sprite.getGlobalBounds(); }

void Base::addSoldat(std::unique_ptr<Defense> soldat) {
  if (soldat) {
    defenses.push_back(std::move(soldat));
  };

}

void Base::death() {
  std::cout << "Base destroyed!" << std::endl;
  // Handle base destruction logic here, e.g., removing from the game
}