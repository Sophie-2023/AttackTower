#include "Soldat.h"
#include "Champ.h"
#include "Base.h"

Soldat::Soldat(sf::Vector2f pos, Base* base_,Champ* p)
    : 
  Defense(5, 3, pos),
  pv(40), 
  vitesse(20),
  texture("res/fermier.png"),
  sprite(texture),
  base(base_) ,
  proprio(p){
  sprite.setScale({0.06f, 0.06f});
  sprite.setOrigin(sprite.getLocalBounds().getCenter()+ sf::Vector2f(0, 250));
  sprite.setPosition(position);
};

void Soldat::draw(sf::RenderWindow& window) const { window.draw(sprite); }

void Soldat::attaquer(Troupe* cible) {}
void Soldat::updateAttaque(sf::Time elapsedTime, TroupeManager& TM) {
  time += elapsedTime.asSeconds();
  if (time >= 5) {
    enMarche = true;
  }
  if (enMarche) {
    sf::Vector2f direction =
        (base->getPosition() - position).normalized() * vitesse;
    position += direction * elapsedTime.asSeconds();
    sprite.move(direction * elapsedTime.asSeconds());
  }
  if ((position-base->getPosition()).length()<5) {
    enMarche = false;
    base->addSoldat(proprio->removeSoldat(this));
  }
}