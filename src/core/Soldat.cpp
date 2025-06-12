#include "Soldat.h"
#include "Champ.h"
#include "Base.h"
#include <iostream>

Soldat::Soldat(sf::Vector2f pos, Base* base_, Champ* p)
    : 
  Defense(150, 3, pos),
  pv(40), 
  vitesse(15),
  texture("res/fermier.png"),
  sprite(texture),
  base(base_) ,
  proprio(p)
{
  sprite.setScale({0.06f, 0.06f});
  sprite.setOrigin(sprite.getLocalBounds().getCenter()+ sf::Vector2f(0, 250));
  sprite.setPosition(position);

  barrePv.setPosition({position.x, position.y - 45.f});
};

void Soldat::draw(sf::RenderWindow& window) const 
{ 
    window.draw(sprite); 
    window.draw(barrePv);
}

void Soldat::attaquer(Troupe* cible_) { 
  cible = cible_;
  attaqueEnCours = true; }


void Soldat::updateAttaque(sf::Time elapsedTime, TroupeManager& TM) {
  time += elapsedTime.asSeconds();
  if (time >= 5 && proprio != nullptr && !proprio->getUnderAttack()) {
    enMarche = true;
  }
  if (enMarche) {
    sf::Vector2f direction =
        (base->getPosition() - position).normalized() * vitesse;
    position += direction * elapsedTime.asSeconds();
    sprite.move(direction * elapsedTime.asSeconds());
    barrePv.setPosition({position.x, position.y - 45.f});
    if (proprio != nullptr && !proprio->getBounds().contains(position)) {
      proprio->moveToSoldatEnRoute(this);
    }
  }
  if ((position - base->getPosition()).length() <
          (base->getBounds().size.x - 100) &&
      proprio != nullptr) {
    base->addSoldat(proprio->removeSoldatEnRoute(this));
    proprio = nullptr;
    enMarche = false;
  }
  if (attaqueEnCours) {
    if (enMarche) {
      attaqueEnCours = false;
    } else {
      if (cible) {
        if ((cible->getPosition() - position).length() < 5) {
          cible->recevoirDegats(degats);
          std::cout << "attaque du fermier" << std::endl;
          attaqueEnCours = false;
        } else {
          sf::Vector2f direction =
              (cible->getPosition() - position).normalized() * vitesse;
          position += direction * elapsedTime.asSeconds();
          sprite.move(direction * elapsedTime.asSeconds());
          barrePv.setPosition({position.x, position.y - 45.f});
        }
      }
    }
  }
  if (proprio == nullptr) {
    if (!underAttack) {
      attaquerBase();
    }
  }
  if (attaqueBase) {
    if (base) {
      if ((base->getPosition() - position).length() < 5) {
        if (time >= 5) {
          time = 0;
          base->recevoirDegats(degats);
          std::cout << "attaque de la base" << std::endl;
          attaqueBase = false;
        }
      } else {
        sf::Vector2f direction =
            (base->getPosition() - position).normalized() * vitesse;
        position += direction * elapsedTime.asSeconds();
        sprite.move(direction * elapsedTime.asSeconds());
        barrePv.setPosition({position.x, position.y - 45.f});
      }
    }
  }
}

void Soldat::attaquerBase() {
  attaqueBase = true;
}