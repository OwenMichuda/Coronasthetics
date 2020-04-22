//
// Created by Owen Michuda on 4/21/2020.
//

#include "mylibrary/exercise.h"

#include <string>

namespace workout {

Exercise :: Exercise(const std::string& name, const std::string& description) {
  name_ = name;
  description_ = description;
}

std::string Exercise :: GetName() {
  return name_;
}

std::string Exercise ::GetDescription() {
  return description_;
}
}