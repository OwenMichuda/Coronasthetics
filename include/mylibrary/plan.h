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
 public:
  bool arms_;
  bool shoulders_;
  bool chest_;
  bool core_;
  bool back_;
  bool legs_;
  std::vector<Exercise> exercises_;
  /** constructor */
  explicit Plan(bool arms, bool shoulders, bool chest,
                bool core, bool back, bool legs);
  /**
   * generates a workout plan, populates the exercises_ vector with
   * exercises from inputted ExerciseDatabase instance
   * @param database where to pull exercises from
   */
  void GeneratePlan(ExerciseDatabase &database);
};

}
#endif  // FINALPROJECT_PLAN_H
