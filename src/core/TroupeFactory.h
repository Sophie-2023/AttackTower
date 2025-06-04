#pragma once
#include "Troupe.h"

class TroupeFactory {
 public:
  Troupe* creerTroupe(const std::string& type);

};
