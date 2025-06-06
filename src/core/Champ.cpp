#include "Champ.h"
#include "TourDeGuet.h"


Champ::Champ(int t, int v, float x, float y)
    : Lieu(sf::Vector2f(x,y)),   taille(t), vie(v), texture("res/champBle.jpg"), sprite(texture) {
  sprite.setOrigin( sprite.getLocalBounds().getCenter());
  sprite.setScale({0.01f*taille, 0.01f*taille});
  sprite.setPosition(sf::Vector2f(x,y));
}
  
void Champ::draw(sf::RenderWindow& window) const { 
  window.draw(sprite);
  for (auto& defense : defenses) {
    defense->draw(window);
  }
  }


void Champ::update(sf::Time elapsedTime, TroupeManager& TM) {
    for (auto& def : defenses) {
      def->update(elapsedTime, TM);
    }
  }

void Champ::addDefense(const std::string& nom, float posx,float posy) {
  if (std::string_view(nom) == "tour") {
    defenses.push_back(
        std::make_unique<TourDeGuet>(posx + position.x, posy + position.y));
  }
}

//void takeDamage(int d);