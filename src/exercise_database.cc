//
// Created by Owen Michuda on 4/21/2020.
//

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\include\mylibrary\exercise_database.h>
#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\include\mylibrary\exercise.h>

namespace workout {

ExerciseDatabase :: ExerciseDatabase(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists exercises (\n"
         "name TEXT NOT NULL, \n"
         "target TEXT NOT NULL, \n"
         "description TEXT NOT NULL\n"
         ");";
}

void ExerciseDatabase :: AddExerciseToDatabase(const Exercise& exercise) {
  db_ << "insert into exercises (name,target,description) values (?,?,?);"
      << exercise.name_
      << exercise.target_area_
      << exercise.description_;
}

std::vector<Exercise> GetExercises(sqlite::database_binder* rows) {
  std::vector<Exercise> exercises;

  for (auto&& row : *rows) {
    std::string name;
    std::string target;
    std::string description;
    row >> name >> target >> description;
    Exercise exercise = Exercise(name, description, target);
    exercises.push_back(exercise);
  }

  return exercises;
}

std::vector<Exercise> ExerciseDatabase::GetTargetExercises(const std::string& target_area, const size_t limit) {
  auto rows = db_ << "select name,target,description "
                     "from exercises "
                     "where target = ? "
                     "limit ? ;"
                  << target_area
                  << limit;


  return GetExercises(&rows);
}

}