#include "TroupeFactory.h"
#include "Chasseur.h"
#include "Loup.h"


std::unique_ptr<Troupe> TroupeFactory::creerTroupe(const std::string& type) {
	if (type == "loup") return std::make_unique<Loup>();
	//if (type == "elephant") return std::make_unique<Elephant>();
	if (type == "chasseur") return std::make_unique<Chasseur>();
	return nullptr;
}
