//
// Created by Owen Michuda on 4/21/2020.
//

#include "mylibrary/plan.h"
#include "mylibrary/exercise_database.h"

namespace workout {

const size_t kLimit = 5;

Plan::Plan(bool arms, bool shoulders, bool chest, bool core, bool back,
                    bool legs) {
  arms_ = arms;
  shoulders_ = shoulders;
  chest_ = chest;
  core_ = core;
  back_ = back;
  legs_ = legs;
}

void Plan::GeneratePlan(ExerciseDatabase database) {
  if (arms_) {
    for (const Exercise& arms_exercise : database.GetTargetExercises("arms", kLimit)) {
      exercises_.push_back(arms_exercise);
    }
  }

  if (shoulders_) {
    for (const Exercise& shoulders_exercise : database.GetTargetExercises("shoulders", kLimit)) {
      exercises_.push_back(shoulders_exercise);
    }
  }

  if (chest_) {
    for (const Exercise& chest_exercise : database.GetTargetExercises("chest", kLimit)) {
      exercises_.push_back(chest_exercise);
    }
  }

  if (core_) {
    for (const Exercise& core_exercise : database.GetTargetExercises("core", kLimit)) {
      exercises_.push_back(core_exercise);
    }
  }

  if (back_) {
    for (const Exercise& back_exercise : database.GetTargetExercises("back", kLimit)) {
      exercises_.push_back(back_exercise);
    }
  }

  if (legs_) {
    for (const Exercise& legs_exercise : database.GetTargetExercises("legs", kLimit)) {
      exercises_.push_back(legs_exercise);
    }
  }
}
Exercise Plan::GetExerciseAtIndex(int index) {
  return exercises_.at(index);
}

}