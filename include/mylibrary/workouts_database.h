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
  sqlite::database db_;
 public:
  explicit WorkoutsDatabase(const std::string& db_path);
  void AddWorkoutToDatabase(const Plan&);
};

}

#endif  // FINALPROJECT_WORKOUTS_DATABASE_H
