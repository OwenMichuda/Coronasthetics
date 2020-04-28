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

}