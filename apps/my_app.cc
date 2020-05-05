// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <gflags/gflags.h>

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

#include <iostream>

namespace myapp {

using std::string;
using std::vector;

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::TextBox;
using cinder::gl::TextureRef;
using cinder::Font;
using cinder::ivec2;

using workout::Exercise;

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

const double kTimeForExercise = 5;
const Color kLightBlue = Color(.678f, .847f, .902f);
const Color kWhite = Color(1, 1, 1);

MyApp::MyApp()
    : plan_(FLAGS_arms, FLAGS_shoulders, FLAGS_chest, FLAGS_core, FLAGS_back, FLAGS_legs),
      workouts_database_(cinder::app::getAssetPath("past_workouts.db").string()),
      add_exercise_{FLAGS_add_exercise},
      current_exercise_(),
      state_{State::kContinue} {
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  /*
  workout::ExerciseDatabase test(cinder::app::getAssetPath("exercises.db").string());
  std::vector<workout::Exercise> core_list = test.GetTargetExercises("core", 5);
  for (workout::Exercise core : core_list) {
    std::cout << core.name_ << std::endl;
  }

  workout::Plan plan = workout::Plan(true, false, true, false, true, false);
  plan.GeneratePlan(test);
  for (workout::Exercise exercise : plan.exercises_) {
    std::cout << exercise.name_ << std::endl;
  }
   */

  workout::ExerciseDatabase exercise_database(cinder::app::getAssetPath("C:\\Users\\Owen Michuda\\Downloads\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project\\assets\\exercises.db").string());

  if (add_exercise_) {
    Exercise new_exercise(FLAGS_exercise_name, FLAGS_exercise_description, FLAGS_exercise_target_area);
    exercise_database.AddExerciseToDatabase(new_exercise);
  }

  plan_.GeneratePlan(exercise_database);
  current_exercise_ = plan_.exercises_.front();
}

void MyApp::update() {
  if (state_ == State::kContinue) {
    if (timer_.isStopped()) {
      timer_.resume();
    }
    if (static_cast<int>(timer_.getSeconds()) == static_cast<int>(kTimeForExercise) + 1) {
      // todo: go to the next exercise
      timer_.start(0);
    }
  }

  if (state_ == State::kFinished) {
    timer_.stop();
    // workouts_database_.AddWorkoutToDatabase(plan_);
  }

  if (state_ == State::kPaused) {
    timer_.stop();
  }

}

void MyApp::DrawBackground() {
  // Light blue
  cinder::gl::clear(kLightBlue);
}

auto GetTextBox(const string& text, const Color& color, const Font& font) -> TextBox {
  TextBox tbox = TextBox()
      .alignment(TextBox::CENTER)
      .font(font)
      .size(TextBox::GROW, TextBox::GROW)
      .color(color)
      .backgroundColor(cinder::ColorA(0, 0, 0, 0))
      .text(text);

  return tbox;
}

void MyApp::DrawTimer() {
  int current_second = static_cast<int>(kTimeForExercise) - static_cast<int>(timer_.getSeconds());
  const string second_to_str = std::to_string(current_second);
  const Font font = Font("Papyrus", 400);
  TextBox timer_tbox = GetTextBox(second_to_str, kWhite, font);
  TextureRef timer_texture = cinder::gl::Texture2d::create(timer_tbox.render());

  const float tbox_size_x = timer_tbox.measure().x;
  const float tbox_size_y = timer_tbox.measure().y;
  const ivec2 loc = {getWindowCenter().x - tbox_size_x / 2,
                        getWindowCenter().y - tbox_size_y / 2};

  cinder::gl::draw(timer_texture, loc);
}

void MyApp::DrawText() {
  const string cur_exercise_name = current_exercise_.name_;
  const Font name_font = Font("Papyrus", 200);
  TextBox name_tbox = GetTextBox(cur_exercise_name, kWhite, name_font);
  TextureRef name_texture = cinder::gl::Texture2d::create(name_tbox.render());

  const float name_tbox_x = name_tbox.measure().x;
  const float name_tbox_y = name_tbox.measure().y;
  const ivec2 name_loc = {getWindowCenter().x - name_tbox_x / 2,
                          getWindowCenter().y / 2 - name_tbox_y / 2};

  cinder::gl::draw(name_texture, name_loc);

  const string cur_exercise_desc = current_exercise_.description_;
  const Font desc_font = Font ("Papyrus", 50);
  TextBox desc_tbox = TextBox()
      .alignment(TextBox::CENTER)
      .font(desc_font)
      .size(getWindowSize().x * (0.75), TextBox::GROW)
      .color(kWhite)
      .backgroundColor(cinder::ColorA(0, 0, 0, 0))
      .text(cur_exercise_desc);
  TextureRef desc_texture = cinder::gl::Texture2d::create(desc_tbox.render());

  const float desc_tbox_x = desc_tbox.measure().x;
  const float desc_tbox_y = desc_tbox.measure().y;
  const ivec2 desc_loc = {getWindowCenter().x - desc_tbox_x / 2,
                          getWindowCenter().y * (1.5) - desc_tbox_y / 2};

  cinder::gl::draw(desc_texture, desc_loc);
}

void MyApp::draw() {
  DrawBackground();
  DrawTimer();
  DrawText();
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
