#include "TroupeFactory.h"
#include "Chasseur.h"

Troupe* TroupeFactory::creerTroupe(const std::string& type) {
	//if (type == "loup") return new Loup();
	//if (type == "elephant") return new Elephant();
	if (type == "chasseur") return new Chasseur();
	return nullptr;
}
