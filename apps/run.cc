// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\cmake-build-debug\_deps\gflags-build\include\gflags\gflags.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "../cmake-build-debug/_deps/gflags-build/include/gflags/gflags.h"
#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;
using std::vector;
using std::string;


namespace myapp {

const int kSamples = 8;
const int kWidth = 1600;
const int kHeight = 1600;

DEFINE_bool(arms, true, "Whether to include arms in the workout");
DEFINE_bool(shoulders, true, "Whether to include shoulders in the workout");
DEFINE_bool(chest, true, "Whether to include chest in the workout");
DEFINE_bool(core, true, "Whether to include core in the workout");
DEFINE_bool(back, true, "Whether to include back in the workout");
DEFINE_bool(legs, true, "Whether to include legs in the workout");

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
