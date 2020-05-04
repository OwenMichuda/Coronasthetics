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
  workout::ExerciseDatabase exercise_database_;
  bool add_exercise_;
  workout::WorkoutsDatabase workouts_database_;
  State state_;
  ci::Timer timer_;
  workout::Exercise current_exercise_;
 private:
  void DrawBackground();
  void DrawTimer();
  void DrawText();
  cinder::TextBox GetTextBox(const std::string& text, const cinder::Color& color, const cinder::Font& font);
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
