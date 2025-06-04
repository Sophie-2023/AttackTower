#pragma once

#include "State.h"
#include "Troupe.h"

class EtatEnRoute : public State {
 public:
  void agir(std::unique_ptr<Troupe> troupe) override;
};