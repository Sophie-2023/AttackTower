#include "Base.h"

Base::Base(const pugi::xml_node& node)
    : Lieu(node), texture("res/champBle.jpg"), sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.2f, 0.2f});
  sprite.setPosition(position);
}

void Base::update(sf::Time elapsedTime, TroupeManager& TM) {
//jsp comment on va update
}

void Base::draw(sf::RenderWindow& window) const { window.draw(sprite); }

sf::FloatRect Base::getBounds() const { return sprite.getGlobalBounds(); }

