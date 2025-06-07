#include "Champ.h"
#include "TourDeGuet.h"
#include "CanonABle.h"
#include <iostream>


Champ::Champ(const pugi::xml_node& node) : Lieu(node) ,
      taille(node.attribute("taille").as_int()),
      vie(node.attribute("vie").as_int()),
      texture("res/champBle.jpg"),
      sprite(texture) {

  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.01f * taille, 0.01f * taille});
  sprite.setPosition(position);

  for (auto& defense : node.children("defense")) {
    std::string type = defense.attribute("type").as_string();
    int xDef = defense.attribute("x").as_int();
    int yDef = defense.attribute("y").as_int();
    addDefense(type, xDef, yDef);

  }
}
  
void Champ::draw(sf::RenderWindow& window) const { 
  window.draw(sprite);
  for (auto& defense : defenses) {
    defense->draw(window);
  }
  }

sf::FloatRect Champ::getBounds() const { return sprite.getGlobalBounds(); }


void Champ::update(sf::Time elapsedTime, TroupeManager& TM) {
    for (auto& def : defenses) {
      def->update(elapsedTime, TM);
    }
  }

void Champ::addDefense(const std::string& type, float posx,float posy) {
  if (std::string_view(type) == "tour") {
    defenses.push_back(
        std::make_unique<TourDeGuet>(posx + position.x, posy + position.y));
  }
  else if (std::string_view(type) == "canon") {
    defenses.push_back(
        std::make_unique<CanonABle>(posx + position.x, posy + position.y));
  }

}

//void takeDamage(int d);