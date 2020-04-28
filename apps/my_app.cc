// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <gflags/gflags.h>

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::TextBox;

DECLARE_bool(add_exercise);
DECLARE_string(exercise_name);
DECLARE_string(exercise_target_area);
DECLARE_string(exercise_description);

DECLARE_bool(arms);
DECLARE_bool(shoulders);
DECLARE_bool(chest);
DECLARE_bool(core);
DECLARE_bool(back);
DECLARE_bool(legs);

MyApp::MyApp()
    : plan_(FLAGS_arms, FLAGS_shoulders, FLAGS_chest, FLAGS_core, FLAGS_back, FLAGS_legs),
      exercise_database_(cinder::app::getAssetPath("exercises.db").string()),
      add_exercise_{FLAGS_add_exercise} {}

void MyApp::setup() {
  if (add_exercise_) {
    workout::Exercise new_exercise(FLAGS_exercise_name, FLAGS_exercise_description, FLAGS_exercise_target_area);
    exercise_database_.AddExerciseToDatabase(new_exercise);
  }
}

void MyApp::update() { }

void MyApp::draw() {}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
