#include <SFML/Graphics.hpp>

#include "Loup.h"
#include <iostream>
#include "EtatExploitation.h"

Loup::Loup(sf::Vector2f pos) 
    : Troupe(100, 100.0f), texture("res/loup.png"), sprite(texture) 
{
  position = pos;
  position.x += 65.f;
  std::cout << "Position du loup : (" << position.x << ", " << position.y << ")"
            << std::endl;
  sprite.setOrigin(sprite.getLocalBounds().getCenter() + sf::Vector2f(0, 130));
  sprite.setScale({0.06f, 0.06f});
  sprite.setPosition(position);
}

void Loup::draw(sf::RenderWindow& window) const {
  window.draw(sprite);

  if (auto* exploitation = dynamic_cast<EtatExploitation*>(etat.get())) {
    exploitation->draw(window);
  }
}

sf::FloatRect Loup::getBounds() const { return sprite.getGlobalBounds(); }
sf::Sprite& Loup::getSprite() { return sprite; }

void Loup::setSelected(bool newBool) {
  Troupe::setSelected(newBool);
  if (newBool) {
    sprite.setColor(sf::Color::Green);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Loup::update(sf::Time elapsedTime) { 
    sf::Vector2f movement(vitesse, 0.f);
    //sprite.move(movement * elapsedTime.asSeconds());
    if (etat) {
      etat->agir(*this, elapsedTime);
    }
}