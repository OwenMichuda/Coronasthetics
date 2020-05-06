//
// Created by Owen Michuda on 4/21/2020.
//

#ifndef FINALPROJECT_EXERCISE_DATABASE_H
#define FINALPROJECT_EXERCISE_DATABASE_H

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\cmake-build-debug\_deps\sqlite-modern-cpp-src\hdr\sqlite_modern_cpp.h>

#include "exercise.h"

#include <vector>
#include <string>

namespace workout {

class ExerciseDatabase {
 private:
  sqlite::database db_;
 public:
  /**
   * constructor
   * @param db_path file path
   */
  explicit ExerciseDatabase(const std::string& db_path);
  /**
   * adds an exercise to the database
   * @param exercise exercise to be added to database
   */
  void AddExerciseToDatabase(const Exercise& exercise);
  /**
   * returns a vector of exercises that correspond to the target_area
   * inputted
   * @param target_area wanted target_area
   * @param limit limit of exercises to be returned
   * @return vector of exercises
   */
  std::vector<Exercise> GetTargetExercises(const std::string& target_area,
                                           const size_t limit);
};

}

#endif  // FINALPROJECT_EXERCISE_DATABASE_H
