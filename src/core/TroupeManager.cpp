#include "TroupeManager.h"
#include "TroupeFactory.h"
#include "Carte.h"
#include "Chasseur.h"
#include "Loup.h"
#include <iostream>

#include "EtatCombat.h"


TroupeManager::TroupeManager() : 
    font("res/Bobatime.ttf"), 
    texteChasseur(font), 
    texteLoup(font),
    textureChasseur("res/chasseur.png"),
    textureLoup("res/loup.png"),
    spriteChasseur(textureChasseur),
    spriteLoup(textureLoup)
{
  texteChasseur.setCharacterSize(30);
  texteChasseur.setFillColor(sf::Color::White);
  texteChasseur.setPosition({480, 10});
  texteLoup.setCharacterSize(30);
  texteLoup.setFillColor(sf::Color::White);
  texteLoup.setPosition({480, 45});

  spriteChasseur.setOrigin(spriteChasseur.getLocalBounds().getCenter() - sf::Vector2f(0, 130));
  spriteChasseur.setScale({0.11f, 0.11f});
  spriteChasseur.setPosition({450, 10});
  spriteLoup.setOrigin(spriteLoup.getLocalBounds().getCenter() -
                           sf::Vector2f(0, 130));
  spriteLoup.setScale({0.045f, 0.045f});
  spriteLoup.setPosition({450, 55});
}

void TroupeManager::initializeTroupe(sf::RenderWindow& window) {
  auto chasseur1 = creerTroupe("chasseur", carte->getBase());
  auto chasseur2 = creerTroupe("chasseur", carte->getBase());
  auto loup = creerTroupe("loup", carte->getBase());
  chasseur1->changerEtat(std::make_unique<EtatCombat>(this, &window));
  chasseur2->changerEtat(std::make_unique<EtatCombat>(this, &window));
  loup->changerEtat(std::make_unique<EtatCombat>(this, &window));
  ajouterTroupe(std::move(chasseur1));
  ajouterTroupe(std::move(chasseur2));
  ajouterTroupe(std::move(loup));
}

void TroupeManager::countTroupe() {
  nbChasseurs = 0;
  nbLoups = 0;

  for (const auto& troupe : troupes) {
    if (dynamic_cast<Chasseur*>(troupe.get())) nbChasseurs++;
    if (dynamic_cast<Loup*>(troupe.get())) nbLoups++;
  }

  texteChasseur.setString("Chasseurs : " + std::to_string(nbChasseurs));
  texteLoup.setString("Loups : " + std::to_string(nbLoups));
    texteChasseur.setString(std::format("Chasseurs : {}", nbChasseurs));
}

void TroupeManager::setCarte(Carte* carte_) { carte = carte_; }

std::unique_ptr<Troupe> TroupeManager::creerTroupe(const std::string& type, Lieu* lieu) {
  return troupeFactory.creerTroupe(type, lieu);
}

void TroupeManager::ajouterTroupe(std::unique_ptr<Troupe> troupe) {
  troupesEnAttente.push_back(std::move(troupe));
}

void TroupeManager::draw(sf::RenderWindow& window) const { 
	for (auto const& troupe : troupes) {
		troupe->draw(window);
	}
    window.draw(texteChasseur);
    window.draw(texteLoup);
    window.draw(spriteChasseur);
    window.draw(spriteLoup);
}

void TroupeManager::update(sf::Time elapsedTime) {
	for (auto const& troupe : troupes) {
		if (troupe) {
		  troupe->update(elapsedTime);
		}
	}

    // On regarde si une des troupes est morte pour l'enlever de la liste des troupes
	for (auto it = troupes.begin(); it != troupes.end(); ) {
        if (*it && (*it)->getPv() <= 0) {
        std::cout << "Troupe supprimée" << std::endl;
        // Libère la mémoire et enlève du vecteur
        it = troupes.erase(it);
        } else {
        ++it;  // Passe à la suivante
        }
    }


    for (auto& newTroupe : troupesEnAttente) {
        troupes.push_back(std::move(newTroupe));
    }
    troupesEnAttente.clear();

    countTroupe();
}