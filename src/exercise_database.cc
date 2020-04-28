//
// Created by Owen Michuda on 4/21/2020.
//

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\include\mylibrary\exercise_database.h>

namespace workout {

ExerciseDatabase :: ExerciseDatabase(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists exercises (\n"
         "name TEXT NOT NULL, \n"
         "target TEXT NOT NULL, \n"
         "description TEXT NOT NULL\n"
         ");";
}

void ExerciseDatabase :: AddExerciseToDatabase(const Exercise& exercise) {
  db_<< "insert into exercises (name,target,description) values (?,?,?);"
     << exercise.name_
     << exercise.target_area_
     << exercise.description_;
}



}