// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/Font.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <mylibrary/exercise.h>
#include <mylibrary/exercise_database.h>
#include <mylibrary/plan.h>
#include <mylibrary/workouts_database.h>

namespace myapp {

enum class State {
  kFinished,
  kPaused,
  kContinue
};

class MyApp : public cinder::app::App {
 private:
  workout::Plan plan_;
  bool add_exercise_;
  bool added_to_past_workouts_;
  State state_;
  ci::Timer timer_;
  workout::Exercise current_exercise_;
  std::vector<workout::Exercise> exercise_vec_;
  std::chrono::time_point<std::chrono::system_clock> last_switch_;
  std::chrono::time_point<std::chrono::system_clock> last_pause_;
  std::chrono::time_point<std::chrono::system_clock> last_resume_;
  int exercise_index_;
 private:
  void DrawBackground();
  void DrawTimer();
  void DrawText();
  void DrawFinish();
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
