#include "Base.h"
#include <iostream>

Base::Base(const pugi::xml_node& node)
    : Lieu(node), texture("res/base.png"), sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.5f, 0.5f});
  sprite.setPosition(position);
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
}

sf::FloatRect Base::getBounds() const { return sprite.getGlobalBounds(); }

void Base::addSoldat(std::unique_ptr<Defense> soldat) {
  if (soldat) {
    defenses.push_back(std::move(soldat));
  };

}