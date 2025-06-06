#include "defense.h"
#include <iostream>


 Defense::Defense(float r, float c, sf::Vector2f pos)
    : rayon(r), cadence(c), cible(nullptr), timer(0.0f),position(pos) {
 }


 void Defense::update(sf::Time elapsedTime, TroupeManager& TM) {
   timer += elapsedTime.asSeconds();
   updateAttaque(elapsedTime,TM);
   float distMin = rayon;
   bool found = false;
   for (auto& troupe : TM.getTroupes()) {
     float dist = (troupe->getPosition() - position).length();

      if (dist <= distMin) {
          cible = troupe.get();
        distMin = dist;
        found = true;

      }
   }
   if (!found) {
     cible = nullptr;
     return;
   }
   
   if (timer > cadence) {
     timer = 0;
     attaquer(cible);
   }
 }
