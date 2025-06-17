#include "defense.h"
#include <iostream>


 Defense::Defense(float r, float c, sf::Vector2f pos,int pv_)
    : rayon(r), cadence(c), cible(nullptr), timer(0.0f),position(pos), pv(pv_), pvMax(pv_) 
 {
   barrePv.setSize({50.f, 5.f});
   barrePv.setFillColor(sf::Color::Magenta);
   barrePv.setOrigin(barrePv.getLocalBounds().getCenter());
 }

 void Defense::recevoirDegats(int amount) {
   pv += amount;
   if (pv <= 0) pv = 0;
   if (pv > pvMax) pv = pvMax;

   float proportion = static_cast<float>(pv) / static_cast<float>(pvMax);
   proportion = std::clamp(proportion, 0.f, 1.f);  // éviter valeur négative
   if (barrePv.getSize().x > 0 && barrePv.getSize().y > 0) {
     barrePv.setSize({50.f * proportion, 5.f});
   }
 }

 void Defense::update(sf::Time elapsedTime, TroupeManager& TM) {

   timer += elapsedTime.asSeconds();
   updateAttaque(elapsedTime,TM);
   if (timer > cadence) {
     float distMin = rayon;
     bool found = false;
     for (auto const& troupe : TM.getTroupes()) {
       float dist = (troupe->getPosition() - position).length();

        if (dist <= distMin) {
            cible = troupe.get();
          distMin = dist;
          found = true;

        }
     }
     if (!found) {
       cible = nullptr;
       underAttack = false;
       return;
     } else {
       timer = 0;
       attaquer(cible);
       underAttack = true;
     }
   }
   
 }
 
 bool Defense::getAttaqueEnCours() { return underAttack; }