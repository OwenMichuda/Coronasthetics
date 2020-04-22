//
// Created by Owen Michuda on 4/21/2020.
//

#ifndef FINALPROJECT_EXERCISE_H
#define FINALPROJECT_EXERCISE_H

#include <string>

namespace workout {

class Exercise {
 private:
  std::string name_;
  std::string description_;
 public:
  Exercise(const std::string& name, const std::string& description);
  std::string GetName();
  std::string GetDescription();
};

}

#endif  // FINALPROJECT_EXERCISE_H
