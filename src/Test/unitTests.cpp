#include <gtest/gtest.h>

#include "TourdeGuet.h"
TEST(TestGame, FirstTest) {
  EXPECT_EQ(1, 1);
}

TEST(Defense, TakeDamage) { 
  TourDeGuet defense(20,20);
  defense.recevoirDegats(-5);
  EXPECT_FLOAT_EQ(defense.getPv(), 95);
}

