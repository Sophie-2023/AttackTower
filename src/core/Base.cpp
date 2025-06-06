#include "Base.h"

Base::Base(float x, float y)
    : Lieu(sf::Vector2f(x, y)), texture("res/champBle.jpg"), sprite(texture) {
  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.2f, 0.2f});
  sprite.setPosition(sf::Vector2f(x, y));
}

void Base::update(sf::Time elapsedTime, TroupeManager& TM) {
//jsp comment on va update
}

void Base::draw(sf::RenderWindow& window) const { window.draw(sprite); }

sf::FloatRect Base::getBounds() const { return sprite.getGlobalBounds(); }

