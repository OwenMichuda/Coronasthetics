// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <cinder/app/AppBase.h>
#include <mylibrary/exercise_database.h>
#include <mylibrary/workouts_database.h>

#include <catch2/catch.hpp>

#include <fstream>

TEST_CASE("Exercise Class") {

  SECTION("Basic constructor") {
    workout::Exercise exercise("test name", "test description",
                               "test target area");
    REQUIRE(exercise.name_ == "test name");
    REQUIRE(exercise.description_ == "test description");
    REQUIRE(exercise.target_area_ == "test target area");
  }

  SECTION("Empty constructor") {
    workout::Exercise exercise = workout::Exercise();
    REQUIRE(exercise.name_ == "");
    REQUIRE(exercise.description_ == "");
    REQUIRE(exercise.target_area_ == "");
  }

  SECTION("Copy constructor") {
    workout::Exercise exercise("test name", "test description",
                               "test target area");
    workout::Exercise copy = exercise;
    REQUIRE(copy.name_ == "test name");
    REQUIRE(copy.description_ == "test description");
    REQUIRE(copy.target_area_ == "test target area");
  }
}

TEST_CASE("Plan Class") {

  SECTION("Constructor") {
    workout::Plan plan(true, false, true,
                       false, true, false);
    REQUIRE(plan.arms_);
    REQUIRE(!plan.shoulders_);
    REQUIRE(plan.chest_);
    REQUIRE(!plan.core_);
    REQUIRE(plan.back_);
    REQUIRE(!plan.legs_);
  }

  SECTION("GeneratePlan function: zero target areas") {
    workout::ExerciseDatabase exercise_database(
        cinder::app::getAssetPath("exercises.db").string());
    workout::Plan plan(false, false, false,
                       false, false, false);
    plan.GeneratePlan(exercise_database);
    REQUIRE(plan.exercises_.empty());
  }

  SECTION("GeneratePlan function: one target area") {
    workout::ExerciseDatabase exercise_database(
        cinder::app::getAssetPath("exercises.db").string());
    workout::Plan plan(false, true, false,
                       false, false, false);
    plan.GeneratePlan(exercise_database);
    REQUIRE(!plan.exercises_.empty());
    REQUIRE(plan.exercises_.size() == 5);
    REQUIRE(plan.exercises_.at(0).name_ == "push ups");
  }

  SECTION("GeneratePlan function: all target areas") {
    workout::ExerciseDatabase exercise_database(
        cinder::app::getAssetPath("exercises.db").string());
    workout::Plan plan(true, true, true,
                       true, true, true);
    plan.GeneratePlan(exercise_database);
    REQUIRE(!plan.exercises_.empty());
    REQUIRE(plan.exercises_.size() == 30);
    REQUIRE(plan.exercises_.front().name_ == "dips");
    REQUIRE(plan.exercises_.back().name_ == "elevated glute bridges");
  }
}

// Make sure to delete the test.db database before running this test.
TEST_CASE("ExerciseDatabase Class") {
  workout::ExerciseDatabase exercise_database(
      "C:\\Users\\Owen Michuda\\Downloads\\cinder_0.9.2_vc2015\\"
      "cinder_0.9.2_vc2015\\my-projects\\final-project\\assets\\test.db");

  SECTION("Constructor: new table") {
    std::vector<workout::Exercise> test_target_exercises =
        exercise_database.GetTargetExercises("arms", 1);
    REQUIRE(test_target_exercises.empty());
  }

  workout::Exercise first_exercise("first name", "first description",
                                   "target area");
  exercise_database.AddExerciseToDatabase(first_exercise);
  SECTION("AddExerciseToDatabase function") {
    std::vector<workout::Exercise> test_target_exercises =
        exercise_database.GetTargetExercises("target area", 1);
    REQUIRE(!test_target_exercises.empty());
    REQUIRE(test_target_exercises.front().name_ == "first name");
    REQUIRE(test_target_exercises.front().description_ == "first description");
    REQUIRE(test_target_exercises.front().target_area_ == "target area");
  }

  workout::Exercise last_exercise("last name", "last description",
                                   "target area");
  exercise_database.AddExerciseToDatabase(last_exercise);
  SECTION("GetTargetExercises function") {
    std::vector<workout::Exercise> test_target_exercises =
        exercise_database.GetTargetExercises("target area", 2);
    REQUIRE(!test_target_exercises.empty());
    REQUIRE(test_target_exercises.front().name_ == "first name");
    REQUIRE(test_target_exercises.front().description_ == "first description");
    REQUIRE(test_target_exercises.front().target_area_ == "target area");
    REQUIRE(test_target_exercises.back().name_ == "last name");
    REQUIRE(test_target_exercises.back().description_ == "last description");
    REQUIRE(test_target_exercises.back().target_area_ == "target area");
  }
}

TEST_CASE("WorkoutsDatabase Class") {
  workout::WorkoutsDatabase workout_database(
      "C:\\Users\\Owen Michuda\\Downloads\\cinder_0.9.2_vc2015\\"
      "cinder_0.9.2_vc2015\\my-projects\\final-project\\assets\\test_1.db");

  SECTION("Constructor: new table") {
    std::ifstream file("C:\\Users\\Owen Michuda\\Downloads\\"
        "cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\"
        "final-project\\assets\\test_1.db");
    REQUIRE(file.good());
  }

  workout::Plan plan(false, true, true,
                       true, true, false);
  SECTION("AddWorkoutToDatabase and RecommendedWorkout functions") {
    workout_database.AddWorkoutToDatabase(plan);
    workout_database.AddWorkoutToDatabase(plan);
    workout_database.AddWorkoutToDatabase(plan);
    std::vector<std::string> recommended_ares =
        workout_database.RecommendedWorkout();
    REQUIRE(!recommended_ares.empty());
    REQUIRE(recommended_ares.front() == "arms");
    REQUIRE(recommended_ares.back() == "legs");

  }
}