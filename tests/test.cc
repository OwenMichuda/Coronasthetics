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

  workout::Plan plan = workout::Plan(true, false, true, false, true, false);
  plan.GeneratePlan(test);
  for (workout::Exercise exercise : plan.exercises_) {
    std::cout << exercise.name_ << std::endl;
  }
}

TEST_CASE("Workouts database") {
  workout::WorkoutsDatabase workout_database((cinder::app::getAssetPath("past_workouts.db").string()));
  workout::ExerciseDatabase exercise_database(cinder::app::getAssetPath("exercises.db").string());
  workout::Plan plan = workout::Plan(true, false, true, false, true, false);
  plan.GeneratePlan(exercise_database);
  workout_database.AddWorkoutToDatabase(plan);
}