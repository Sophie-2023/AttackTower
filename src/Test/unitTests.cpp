#include <gtest/gtest.h>
#include "pugixml.hpp"
#include "TourdeGuet.h"
#include "Champ.h"
#include "Lieu.h"
#include "Chasseur.h"
#include "Carte.h"
#include "Game.h"


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


  sf::RenderWindow mWindow{sf::VideoMode({1280, 720}), "Attack Tower Game"};
  Game game(mWindow);
  Carte carte;
  pugi::xml_document doc;
  if (auto result = doc.load_file("res/map.xml"); !result) {
    std::cerr << "Could not open file visage.xml because "
              << result.description() << std::endl;
  }
  pugi::xml_node nodeSource = doc.child("map");
  carte.makeCarte(nodeSource, &game);

  Chasseur chasseur(carte.getBase());

  int pvInitial = chasseur.getPv();
  int degats = 10;

  chasseur.recevoirDegats(-degats);

  EXPECT_EQ(chasseur.getPv(), pvInitial - degats);
}