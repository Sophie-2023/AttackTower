#include "Champ.h"
#include "TourDeGuet.h"
#include "CanonABle.h"
#include <iostream>


Champ::Champ(const pugi::xml_node& node,Base* b) : Lieu(node) ,
      taille(node.attribute("taille").as_int()),
      texture("res/champBle.jpg"),
      sprite(texture),
      base(b){

  sprite.setOrigin(sprite.getLocalBounds().getCenter());
  sprite.setScale({0.05f * taille, 0.05f * taille});
  sprite.setPosition(position);
  barrePv.setFillColor(sf::Color::Yellow);
  barrePv.setSize({25.f*taille, 5.f});
  prop = sf::Vector2f(25.f * taille, 5.f);
  barrePv.setOrigin(barrePv.getLocalBounds().getCenter());
  barrePv.setPosition(sf::Vector2f(position.x, position.y - sprite.getGlobalBounds().size.y / 2 - 20));

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
  for (auto& soldat : soldatsEnRoute) {
    if (soldat) {
      soldat->draw(window);
    }
  }
  window.draw(barrePv);
}

sf::FloatRect Champ::getBounds() const { return sprite.getGlobalBounds(); }


void Champ::update(sf::Time elapsedTime, TroupeManager& TM) {
  troupeManager = &TM;
  underAttack = false;
    for (auto& def : defenses) {
      if (def) {
        if (def->getAttaqueEnCours()) {
          underAttack = true;
        }
        def->update(elapsedTime, TM);

      }
    }
    for (auto& soldat : soldatsEnRoute) {
      if (soldat) {
        soldat->update(elapsedTime, TM);
      }
    }
    if (isAlive()) {
      // spawn des soldats
      timeSinceLastSpawn += elapsedTime.asSeconds();
      if (timeSinceLastSpawn >= spawnInterval) {
        addSoldat();
        timeSinceLastSpawn = 0.0f;
      }
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

void Champ::moveToSoldatEnRoute(const Defense* soldat) {
  auto it = std::find_if(defenses.begin(), defenses.end(),
                         [soldat](const std::unique_ptr<Defense>& s) {
                           return s.get() == soldat;
                         });
  if (it != defenses.end()) {
    std::unique_ptr<Defense> removedSoldat = std::move(*it);
    defenses.erase(it);
    soldatsEnRoute.push_back(std::move(removedSoldat));
  }
}
std::unique_ptr<Defense> Champ::removeSoldatEnRoute(Defense* soldat) {
  auto it = std::find_if(soldatsEnRoute.begin(), soldatsEnRoute.end(),
                         [soldat](const std::unique_ptr<Defense>& s) {
                           return s.get() == soldat;
                         });
  if (it != soldatsEnRoute.end()) {
    std::unique_ptr<Defense> removedSoldat = std::move(*it);
    soldatsEnRoute.erase(it);
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

void Champ::death() {
  for (int i =0;i<taille;i++) {
    std::unique_ptr<Troupe> newTroupe =
        troupeManager->creerTroupe("chasseur", this);
    newTroupe->setIsInBase(false);
    troupeManager->ajouterTroupe(std::move(newTroupe));
  }

}