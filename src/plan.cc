//
// Created by Owen Michuda on 4/21/2020.
//

#include "mylibrary/plan.h"
namespace workout {

Plan::Plan(bool arms, bool shoulders, bool chest, bool core, bool back,
                    bool legs) {
  arms_ = arms;
  shoulders_ = shoulders;
  chest_ = chest;
  core_ = core;
  back_ = back;
  legs_ = legs;
}


}