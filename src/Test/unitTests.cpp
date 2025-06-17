#include <gtest/gtest.h>
#include "pugixml.hpp"
#include "TourdeGuet.h"
#include "Champ.h"
#include "Lieu.h"
#include "Chasseur.h"
#include "Carte.h"




TEST(Defense, TakeDamage) { 
  TourDeGuet defense(20,20);
  defense.recevoirDegats(-5);
  EXPECT_FLOAT_EQ(defense.getPv(), 95);
}
TEST(Champ, makeTour) {
  std::string sg = R"(<?xml version = "1.0"?>

                       <champ x="640" y="600" taille="2" vie="100">
<defense type="tour" x="50" y="50"/>
</champ>)";

  pugi::xml_document doc;
  doc.load_string(sg.c_str());
  pugi::xml_node node = doc.child("champ");
  Champ champ(node, nullptr);
  EXPECT_EQ(champ.getDefenses().size(), 1);
  TourDeGuet* tour = dynamic_cast<TourDeGuet*>(champ.getDefenses()[0].get());
  EXPECT_TRUE( tour!=nullptr);
}

TEST(Champ, addSoldat) { 
  std::string sg = R"(<?xml version = "1.0"?>
                       <champ x="640" y="600" taille="2" vie="100"/>)";
  
  pugi::xml_document doc;
  doc.load_string(sg.c_str());
  pugi::xml_node node = doc.child("champ");
  Champ champ(node, nullptr);
  champ.addSoldat();
  EXPECT_EQ(champ.getDefenses().size(), 1);
}



TEST(ChasseurTest, RecevoirDegatsReduitPv) {


  std::string sg = R"(<?xml version = "1.0"?>
                       <champ x="40" y="40" taille="2" vie="100"/>)";
                    
  pugi::xml_document doc;
  doc.load_string(sg.c_str());
  pugi::xml_node node = doc.child("champ");
  Champ champ(node, nullptr);

  Chasseur chasseur(&champ);

  int pvInitial = chasseur.getPv();
  int degats = 10;

  chasseur.recevoirDegats(-degats);

  EXPECT_EQ(chasseur.getPv(), pvInitial - degats);
}

TEST(ChasseurTest, AttaqueToucheEtInfligeDegats) {

  std::string sg = R"(<?xml version = "1.0"?>
                       <champ x="40" y="40" taille="2" vie="100">
                        <defense type="tour" x="50" y="50"/>
                        </champ>)";

  pugi::xml_document doc;
  doc.load_string(sg.c_str());
  pugi::xml_node node = doc.child("champ");
  Champ champ(node, nullptr);

  TourDeGuet defense(50, 50);

  Chasseur chasseur(&champ);

  int pvAvant = defense.getPv();
  chasseur.setPosition({49.f, 49.f});
  chasseur.attaquer(&defense);

  for (int i = 0; i < 100; ++i) {
    chasseur.updateAttaque(sf::seconds(0.1f));
  }

  EXPECT_EQ(defense.getPv(), pvAvant - chasseur.getDegats());
}

TEST(ChasseurTest, PeutAttaquerUnChamp) {

  std::string sg = R"(<?xml version = "1.0"?>
                       <champ x="40" y="40" taille="2" vie="100"/>)";

  pugi::xml_document doc;
  doc.load_string(sg.c_str());
  pugi::xml_node node = doc.child("champ");
  Champ champ(node, nullptr);

  Chasseur chasseur(&champ);
  chasseur.setPosition({39.f, 39.f});

  int pvAvant = champ.getPv();

  chasseur.attaquer(nullptr);  // pas de cible -> attaque le lieu 
  for (int i = 0; i < 100; ++i) {
    chasseur.updateAttaque(sf::seconds(0.1f));
  }

  EXPECT_EQ(champ.getPv(), pvAvant - chasseur.getDegats());
}
