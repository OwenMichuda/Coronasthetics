//
// Created by Owen Michuda on 4/21/2020.
//

#include "mylibrary/exercise.h"

#include <string>

namespace workout {

Exercise :: Exercise(const std::string& name, const std::string& description,
    const std::string& target_area) {
  name_ = name;
  description_ = description;
  target_area_ = target_area;
}
Exercise::Exercise() {
  name_ = "";
  description_ = "";
  target_area_ = "";
}
Exercise::Exercise(const Exercise& exercise) {
  name_ = exercise.name_;
  description_ = exercise.description_;
  target_area_ = exercise.target_area_;
}

}