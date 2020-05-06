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

  database_ << "insert into workouts (date,arms,shoulders,chest,core,back,legs) "
               "values (?,?,?,?,?,?,?);"
      << date_str
      << arms
      << shoulders
      << chest
      << core
      << back
      << legs;
}

std::vector<std::string> WorkoutsDatabase::RecommendedWorkout() {
  auto rows = database_ <<  "select arms,shoulders,chest,core,back,legs "
                            "from workouts "
                            "order by date desc "
                            "limit 3 ;";

  int arms_count = 0;
  int shoulders_count = 0;
  int chest_count = 0;
  int core_count = 0;
  int back_count = 0;
  int legs_count = 0;
  for (auto&& row : rows) {
    std::string arms;
    std::string shoulders;
    std::string chest;
    std::string core;
    std::string back;
    std::string legs;
    row >> arms >> shoulders >> chest >> core >> back >> legs;
    if (arms == "TRUE") {
      ++arms_count;
    }
    if (shoulders == "TRUE") {
      ++shoulders_count;
    }
    if (chest == "TRUE") {
      ++chest_count;
    }
    if (core == "TRUE") {
      ++core_count;
    }
    if (back == "TRUE") {
      ++back_count;
    }
    if (legs == "TRUE") {
      ++legs_count;
    }
  }

  std::vector<std::string> results;
  if (arms_count == 0) {
    results.emplace_back("arms");
  }
  if (shoulders_count == 0) {
    results.emplace_back("shoulders");
  }
  if (chest_count == 0) {
    results.emplace_back("chest");
  }
  if (core_count == 0) {
    results.emplace_back("core");
  }
  if (back_count == 0) {
    results.emplace_back("back");
  }
  if (legs_count == 0) {
    results.emplace_back("legs");
  }

  if (results.empty()) {
    if (arms_count == 1) {
      results.emplace_back("arms");
    }
    if (shoulders_count == 1) {
      results.emplace_back("shoulders");
    }
    if (chest_count == 1) {
      results.emplace_back("chest");
    }
    if (core_count == 1) {
      results.emplace_back("core");
    }
    if (back_count == 1) {
      results.emplace_back("back");
    }
    if (legs_count == 1) {
      results.emplace_back("legs");
    }
  }

  if (results.empty()) {
    if (arms_count == 2) {
      results.emplace_back("arms");
    }
    if (shoulders_count == 2) {
      results.emplace_back("shoulders");
    }
    if (chest_count == 2) {
      results.emplace_back("chest");
    }
    if (core_count == 2) {
      results.emplace_back("core");
    }
    if (back_count == 2) {
      results.emplace_back("back");
    }
    if (legs_count == 2) {
      results.emplace_back("legs");
    }
  }

  return results;
}

}