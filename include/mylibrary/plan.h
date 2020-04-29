//
// Created by Owen Michuda on 4/21/2020.
//

#ifndef FINALPROJECT_PLAN_H
#define FINALPROJECT_PLAN_H

#include "exercise.h"
#include "exercise_database.h"

#include <string>
#include <vector>

namespace workout {

class Plan {
 private:
  bool arms_;
  bool shoulders_;
  bool chest_;
  bool core_;
  bool back_;
  bool legs_;
 public:
  std::vector<Exercise> exercises_;
  explicit Plan(bool arms, bool shoulders, bool chest, bool core, bool back, bool legs);
  void GeneratePlan(ExerciseDatabase database);
};

}
#endif  // FINALPROJECT_PLAN_H
