#include "TroupeManager.h"
#include "TroupeFactory.h"
#include "Carte.h"
#include "Chasseur.h"
#include "Loup.h"
#include "Elephant.h"
#include "Game.h"
#include <iostream>

#include "EtatCombat.h"


TroupeManager::TroupeManager() : 
    font("res/Bobatime.ttf"), 
    texteChasseur(font), 
    texteLoup(font),
    texteElephant(font),
    textureChasseur("res/chasseur.png"),
    textureLoup("res/loup.png"),
    textureElephant("res/elephant.png"),
    spriteChasseur(textureChasseur),
    spriteLoup(textureLoup),
    spriteElephant(textureElephant) 
{
  texteChasseur.setCharacterSize(30);
  texteChasseur.setFillColor(sf::Color::White);
  texteChasseur.setPosition({480, 10});
  texteLoup.setCharacterSize(30);
  texteLoup.setFillColor(sf::Color::White);
  texteLoup.setPosition({480, 45});
  texteElephant.setCharacterSize(30);
  texteElephant.setFillColor(sf::Color::White);
  texteElephant.setPosition({480, 80});

  spriteChasseur.setOrigin(spriteChasseur.getLocalBounds().getCenter() - sf::Vector2f(0, 130));
  spriteChasseur.setScale({0.11f, 0.11f});
  spriteChasseur.setPosition({450, 10});
  spriteLoup.setOrigin(spriteLoup.getLocalBounds().getCenter() -
                           sf::Vector2f(0, 130));
  spriteLoup.setScale({0.045f, 0.045f});
  spriteLoup.setPosition({450, 55});
  spriteElephant.setOrigin(spriteElephant.getLocalBounds().getCenter());
  spriteElephant.setScale({1.2f, 1.2f});
  spriteElephant.setPosition({450, 100});
}

void TroupeManager::initializeTroupe(sf::RenderWindow& window) {
  auto chasseur1 = creerTroupe("chasseur", carte->getBase());
  auto chasseur2 = creerTroupe("chasseur", carte->getBase());
  auto loup = creerTroupe("loup", carte->getBase());
  auto loup2 = creerTroupe("loup", carte->getBase());
  auto elephant = creerTroupe("elephant", carte->getBase());
  auto elephant2 = creerTroupe("elephant", carte->getBase());
  chasseur1->changerEtat(std::make_unique<EtatCombat>(this, &window));
  chasseur2->changerEtat(std::make_unique<EtatCombat>(this, &window));
  loup->changerEtat(std::make_unique<EtatCombat>(this, &window));
  loup2->changerEtat(std::make_unique<EtatCombat>(this, &window));
  elephant->changerEtat(std::make_unique<EtatCombat>(this, &window));
  elephant2->changerEtat(std::make_unique<EtatCombat>(this, &window));
  ajouterTroupe(std::move(elephant));
  ajouterTroupe(std::move(elephant2));
  ajouterTroupe(std::move(chasseur1));
  ajouterTroupe(std::move(chasseur2));
  ajouterTroupe(std::move(loup));
  ajouterTroupe(std::move(loup2));
}

void TroupeManager::countTroupe() {
  nbChasseurs = 0;
  nbLoups = 0;
  nbElephants = 0;

  for (const auto& troupe : troupes) {
    if (dynamic_cast<Chasseur*>(troupe.get())) nbChasseurs++;
    if (dynamic_cast<Loup*>(troupe.get())) nbLoups++;
    if (dynamic_cast<Elephant*>(troupe.get())) nbElephants++;
  }

  texteChasseur.setString(std::format("Chasseurs : {}", nbChasseurs));
  texteLoup.setString(std::format("Loups : {}", nbLoups));
  texteElephant.setString(std::format("Elephants : {}", nbElephants));
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
    window.draw(texteElephant);
    window.draw(spriteChasseur);
    window.draw(spriteLoup);
    window.draw(spriteElephant);
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
            if (gameManager &&
                gameManager->getTroupeSelectionnee() == it->get()) {
              gameManager->setTroupeSelectionnee(nullptr);
            }
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