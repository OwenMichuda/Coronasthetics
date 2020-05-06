//
// Created by Owen Michuda on 4/21/2020.
//

#ifndef FINALPROJECT_EXERCISE_H
#define FINALPROJECT_EXERCISE_H

#include <string>

namespace workout {

class Exercise {
 public:
  std::string name_;
  std::string description_;
  std::string target_area_;
  /** constructors */
  Exercise(const std::string& name, const std::string& description,
      const std::string& target_area);
  Exercise();
  Exercise(const Exercise& exercise);
};

}

#endif  // FINALPROJECT_EXERCISE_H
