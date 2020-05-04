// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <cinder/app/AppBase.h>
#include <mylibrary/exercise_database.h>
#include <mylibrary/workouts_database.h>

#include <catch2/catch.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Testing GetExercises") {
  workout::ExerciseDatabase test(cinder::app::getAssetPath("exercises.db").string());
  std::vector<workout::Exercise> core_list = test.GetTargetExercises("core", 5);
  for (workout::Exercise core : core_list) {
    std::cout << core.name_ << std::endl;
  }
}