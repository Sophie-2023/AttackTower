#include "Champ.h"
#include "TourDeGuet.h"
#include "CanonABle.h"
#include <iostream>


Champ::Champ(const pugi::xml_node& node,Base* b) : Lieu(node) ,
      taille(node.attribute("taille").as_int()),
      vie(node.attribute("vie").as_int()),
      texture("res/champBle.jpg"),
      sprite(texture),
      base(b){

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
    if (defense) {
      defense->draw(window);
    }
  }
}

sf::FloatRect Champ::getBounds() const { return sprite.getGlobalBounds(); }


void Champ::update(sf::Time elapsedTime, TroupeManager& TM) {
  underAttack = false;
    for (auto& def : defenses) {
      if (def) {
        if (def->getAttaqueEnCours()) {
          underAttack = true;
        }
        def->update(elapsedTime, TM);

      }
    }
    //spawn des soldats
    timeSinceLastSpawn += elapsedTime.asSeconds();
    if (timeSinceLastSpawn >= spawnInterval) {
        addSoldat();
        timeSinceLastSpawn = 0.0f;
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

std::unique_ptr<Defense> Champ::removeSoldat(Defense* soldat) {
  auto it = std::find_if(defenses.begin(), defenses.end(),
                         [soldat](const std::unique_ptr<Defense>& s) {
                           return s.get() == soldat;
                         });
  if (it != defenses.end()) {
    std::unique_ptr<Defense> removedSoldat = std::move(*it);
    defenses.erase(it);
    return std::move(removedSoldat);
  }
  return nullptr;
}

int random_nMin_to_nMax(int const nMin, int const nMax) {
  static std::random_device rd;
  static std::default_random_engine engine(rd());
  std::uniform_int_distribution distribution(nMin, nMax);
  return distribution(engine);
}

void Champ::addSoldat() {
  sf::FloatRect bounds = sprite.getGlobalBounds();
  int x = random_nMin_to_nMax(-bounds.size.x/2+15, bounds.size.x/2-15);
  int y = random_nMin_to_nMax(-bounds.size.y/2+15, bounds.size.y/2-15);
  defenses.push_back(std::make_unique<Soldat>(sf::Vector2f(position.x+x,position.y+y), base, this));
}

bool Champ::getUnderAttack() { return underAttack; }

//void takeDamage(int d);