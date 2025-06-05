#include "defense.h"

 Defense::Defense(float r, float c, sf::Vector2f pos)
    : rayon(r), cadence(c), cible(nullptr), timer(0.0f),position(pos) {
 }


 void Defense::update(float dt, TroupeManager TM) {
   float distMin = rayon + 1.f;
   for (auto& troupe : TM.getTroupes()) {
     float dist = (troupe->getPosition() - position).length();
      if (dist < distMin) {
      if (dist < rayon) {
        cible = troupe.get();
      }
      }
   }
   if (distMin > rayon) {
     cible = nullptr;
     return;
   }
   timer += dt;
   if (timer > cadence) {
     timer = 0;
     attaquer(cible);
   }
 }
