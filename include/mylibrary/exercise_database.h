//
// Created by Owen Michuda on 4/21/2020.
//

#ifndef FINALPROJECT_EXERCISE_DATABASE_H
#define FINALPROJECT_EXERCISE_DATABASE_H

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\cmake-build-debug\_deps\sqlite-modern-cpp-src\hdr\sqlite_modern_cpp.h>

#include "exercise_database.h"
#include "exercise.h"

#include <vector>
#include <string>

namespace workout {

class ExerciseDatabase {
 private:
  sqlite::database db_;
 public:
  explicit ExerciseDatabase(const std::string& db_path);
  void AddExerciseToDatabase(const Exercise&);
  std::vector<Exercise> GetTargetExercises(const std::string& target_area, const size_t limit);
};

}

#endif  // FINALPROJECT_EXERCISE_DATABASE_H
