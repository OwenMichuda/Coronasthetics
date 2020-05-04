//
// Created by Owen Michuda on 4/28/2020.
//

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\include\mylibrary\workouts_database.h>
#include <ctime>

namespace workout {

WorkoutsDatabase :: WorkoutsDatabase(const std::string& db_path) : database_{db_path} {
  database_ << "CREATE TABLE if not exists workouts (\n"
         "date TEXT NOT NULL, \n"
         "exercises TEXT NOT NULL\n"
         ");";
}

void WorkoutsDatabase :: AddWorkoutToDatabase(const Plan& plan) {
  // This is for the local date and time, learned here:
  // https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
  time_t now = time(0);
  char* date = ctime(&now);
  std::string date_str(date);

  // This takes all the exercises and changes it into one string
  std::string exercises_str;
  for (Exercise exercise : plan.exercises_) {
    exercises_str.append(exercise.name_);
    while (exercise.name_ != plan.exercises_.back().name_) {
      exercises_str.append(", ");
    }
  }

  database_ << "insert into workouts (date,exercises) values (?,?);"
      << "test"
      << exercises_str;
}

}