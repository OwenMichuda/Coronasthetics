// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <gflags/gflags.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;
using std::vector;
using std::string;


namespace myapp {

const int kSamples = 8;
const int kWidth = 1600;
const int kHeight = 1600;

DEFINE_bool(add_exercise, false, "Whether to add a new exercise to the database");
DEFINE_string(exercise_name, "crunches", "The name of the exercise");
DEFINE_string(exercise_target_area, "core", "The target area of the exercise");
DEFINE_string(exercise_description, "laying with your back on the ground and your"
              " knees bent, curl your torso up until your shoulder blades are off"
              " the floor.", "The description of the exercise");

DEFINE_bool(arms, true, "Whether to include arms in the workout");
DEFINE_bool(shoulders, false, "Whether to include shoulders in the workout");
DEFINE_bool(chest, false, "Whether to include chest in the workout");
DEFINE_bool(core, false, "Whether to include core in the workout");
DEFINE_bool(back, false, "Whether to include back in the workout");
DEFINE_bool(legs, false, "Whether to include legs in the workout");

void ParseArgs(vector<string>* args) {
  gflags::SetUsageMessage(
      "Create a workout plan. Pass --helpshort for options.");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);

  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
}

}  // namespace myapp

// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
