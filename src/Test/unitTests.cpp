#include <gtest/gtest.h>

#include "TourdeGuet.h"
#include "Chasseur.h"
#include "Carte.h"
#include "Game.h"


TEST(Defense, TakeDamage) { 
  TourDeGuet defense(20,20);
  defense.recevoirDegats(-5);
  EXPECT_FLOAT_EQ(defense.getPv(), 95);
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