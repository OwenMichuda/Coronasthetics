//
// Created by Owen Michuda on 4/28/2020.
//

#ifndef FINALPROJECT_WORKOUTS_DATABASE_H
#define FINALPROJECT_WORKOUTS_DATABASE_H

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\cmake-build-debug\_deps\sqlite-modern-cpp-src\hdr\sqlite_modern_cpp.h>

#include "plan.h"

#include <string>

namespace workout {

class WorkoutsDatabase {
 private:
  sqlite::database database_;
 public:
  /**
   * constructor
   * @param db_path file path
   */
  explicit WorkoutsDatabase(const std::string& db_path);
  /**
   * adds an instance of plan class to this database
   * @param plan plan to be added to database
   */
  void AddWorkoutToDatabase(const Plan& plan);
  /**
   * algorithm that determines what target areas the user should target
   * next time they workout
   * @return vector of strings corresponding to the target areas
   */
  std::vector<std::string> RecommendedWorkout();
};

}

#endif  // FINALPROJECT_WORKOUTS_DATABASE_H
