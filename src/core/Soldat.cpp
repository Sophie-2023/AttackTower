#include "Soldat.h"
#include "Champ.h"
#include "Base.h"
#include <iostream>

Soldat::Soldat(sf::Vector2f pos, Base* base_, Champ* p)
    : 
  Defense(300, 3, pos,50), 
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
    if (pv <= 0) return;
    window.draw(sprite); 
    window.draw(barrePv);
}

void Soldat::attaquer(Troupe* cible_) { 
 
    cible = cible_;
    attaqueEnCours = true;
}


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
    flip(direction);
    barrePv.setPosition({position.x, position.y - 45.f});

    //si on sort du champ
    if (!dansEnRoute && proprio != nullptr && !proprio->getBounds().contains(position)) {
      proprio->moveToSoldatEnRoute(this);
      dansEnRoute = true;
    }

    // si on arrive a la base
    if (proprio != nullptr && (position - base->getPosition()).length() <
                                  (base->getBounds().size.x / 2 + 50)) {
      base->addSoldat(proprio->removeSoldatEnRoute(this));
      proprio = nullptr;
      enMarche = false;
    }
  }
  else if (attaqueEnCours) {
    if ((cible->getPosition() - base->getPosition()).length() < base->getBounds().size.x / 2 + 50 ||
        (proprio != nullptr && (cible->getPosition() - proprio->getPosition()).length() < proprio->getBounds().size.x / 2 + 50)) {
        if ((cible->getPosition() - position).length() < 5) {
          cible->recevoirDegats(degats);
          attaqueEnCours = false;
        } else {
          sf::Vector2f direction =
              (cible->getPosition() - position).normalized() * vitesse;
          position += direction * elapsedTime.asSeconds();
          sprite.move(direction * elapsedTime.asSeconds());
          flip(direction);
          barrePv.setPosition({position.x, position.y - 45.f});
        }
        attaqueBase = false;
    } else {
      underAttack = false;
    }
  }
  if (proprio == nullptr && !underAttack) {
      attaquerBase();
    }
  if (attaqueBase && base->isAlive()) {
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
        flip(direction);
        barrePv.setPosition({position.x, position.y - 45.f});
      }
  }
}

void Soldat::attaquerBase() {
  attaqueBase = true;
}
void Soldat::flip(sf::Vector2f direction) {
  if (direction.x < 0) {
    sprite.setScale({-std::abs(sprite.getScale().x), sprite.getScale().y});
  } else if (direction.x > 0) {
    sprite.setScale({std::abs(sprite.getScale().x), sprite.getScale().y});
  }
}