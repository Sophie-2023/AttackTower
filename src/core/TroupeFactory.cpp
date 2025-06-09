#include "TroupeFactory.h"
#include "Chasseur.h"
#include "Loup.h"
#include <iostream>


std::unique_ptr<Troupe> TroupeFactory::creerTroupe(const std::string& type, sf::Vector2f pos) {
  if (type == "loup") {
    return std::make_unique<Loup>(pos);
  }
	//if (type == "elephant") return std::make_unique<Elephant>(pos);
	if (type == "chasseur") return std::make_unique<Chasseur>(pos);
	return nullptr;
}
