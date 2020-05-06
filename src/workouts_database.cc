//
// Created by Owen Michuda on 4/28/2020.
//

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\include\mylibrary\workouts_database.h>
#include <ctime>

namespace workout {

WorkoutsDatabase :: WorkoutsDatabase(const std::string& db_path) : database_{db_path} {
  database_ << "CREATE TABLE if not exists workouts (\n"
         "date TEXT NOT NULL, \n"
         "arms BOOLEAN, \n"
         "shoulders BOOLEAN, \n"
         "chest BOOLEAN, \n"
         "core BOOLEAN, \n"
         "back BOOLEAN, \n"
         "legs BOOLEAN\n"
         ");";
}

void WorkoutsDatabase :: AddWorkoutToDatabase(const Plan& plan) {
  // This is for the local date and time, learned here:
  // https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
  time_t now = time(0);
  char* date = ctime(&now);
  std::string date_str(date);

  std::string arms;
  if (plan.arms_) {
    arms = "TRUE";
  } else {
    arms = "FALSE";
  }

  std::string shoulders;
  if (plan.shoulders_) {
    shoulders = "TRUE";
  } else {
    shoulders = "FALSE";
  }

  std::string chest;
  if (plan.chest_) {
    chest = "TRUE";
  } else {
    chest = "FALSE";
  }

  std::string core;
  if (plan.core_) {
    core = "TRUE";
  } else {
    core = "FALSE";
  }

  std::string back;
  if (plan.back_) {
    back = "TRUE";
  } else {
    back = "FALSE";
  }

  std::string legs;
  if (plan.legs_) {
    legs = "TRUE";
  } else {
    legs = "FALSE";
  }

  database_ << "insert into workouts (date,arms,shoulders,chest,core,back,legs) values (?,?,?,?,?,?,?);"
      << date_str
      << arms
      << shoulders
      << chest
      << core
      << back
      << legs;
}

}