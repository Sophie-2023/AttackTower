#include "Base.h"
#include <iostream>
 #include "Carte.h"

Base::Base(const pugi::xml_node& node,Carte* carte_)
    : Lieu(node), texture("res/base.png"), sprite(texture), carte(carte_) {
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
  for (auto const& soldat : defenses) {
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
  carte->End(false);
}