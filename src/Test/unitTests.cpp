#include <gtest/gtest.h>
#include "pugixml.hpp"
#include "TourdeGuet.h"
#include "Champ.h"
#include "Lieu.h"
TEST(TestGame, FirstTest) {
  EXPECT_EQ(1, 1);
}

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



