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
#include <chrono>


namespace myapp {

using std::string;
using std::vector;
using std::chrono::seconds;
using std::chrono::system_clock;

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

const int kTimeForExercise = 5;
const Color kLightBlue = Color(.678f, .847f, .902f);
const Color kWhite = Color(1, 1, 1);

MyApp::MyApp()
    : plan_(FLAGS_arms, FLAGS_shoulders, FLAGS_chest,
            FLAGS_core, FLAGS_back, FLAGS_legs),
      add_exercise_{FLAGS_add_exercise},
      current_exercise_(),
      added_to_past_workouts_{false},
      exercise_index_(-1),
      exercise_vec_(),
      state_{State::kContinue} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  workout::ExerciseDatabase exercise_database(
      "C:\\Users\\Owen Michuda\\Downloads\\cinder_0.9.2_vc2015\\"
      "cinder_0.9.2_vc2015\\my-projects\\final-project\\assets"
      "\\exercises.db");

  if (add_exercise_) {
    Exercise new_exercise(FLAGS_exercise_name, FLAGS_exercise_description,
                          FLAGS_exercise_target_area);
    exercise_database.AddExerciseToDatabase(new_exercise);
  }

  /*
  plan_.exercises_.clear();
  plan_.GeneratePlan(exercise_database);
  current_exercise_ = plan_.exercises_.front();
  */

  // Unfortunately the database querying isn't working, even after two office
  // hour sessions and multiple piazza posts. The TA's recommend I use a
  // temporary vector of Exercise instances instead.
  if (FLAGS_arms) {
    exercise_vec_.emplace_back(
        Exercise("dips", "position yourself on an elevated "
                 "surface, with your hands shoulder width apart. slide your butt"
                 " off the front off the surface. lower yourself down until your"
                 " elbows form a 90 degree angle. push yourself back up.",
                 "arms"));
    exercise_vec_.emplace_back(
        Exercise("diamond push ups", "get into the push up"
                 " position, but with your hands close together, forming a"
                 " diamond with your fingers. lower yourself down until your"
                 " chest is barely above the ground, and push yourself back up.",
                 "arms"));
    exercise_vec_.emplace_back(
        Exercise("chin ups", "grip an overhead bar with a "
                 "supinated grip, shoulder width apart. pull your chip up towards"
                 " the bar, as high as possible. lower yourself back down.",
                 "arms"));
    exercise_vec_.emplace_back(
        Exercise("five finger high planks", "get into the push up"
                 " position, but push yourself up so your weight is only on your"
                 " fingers and your palms are not touching the ground. hold this"
                 " position.", "arms"));
    exercise_vec_.emplace_back(
        Exercise("inverted rows", "position yourself underneath"
                 " a bar about waist height. grab the bar with an overhead grip,"
                 " slightly wider than shoulder width. pull yourself up until your"
                 " chest is almost touching the bar. lower yourself back down.",
                 "arms"));
  }

  if (FLAGS_back) {
    exercise_vec_.emplace_back(
        Exercise("superman", "lay down on the floor, with arms"
                 " and legs completely extended. lift your arms and legs slightly"
                 " off the ground, so your weight is on your stomach. hold this"
                 " position.", "back"));
    exercise_vec_.emplace_back(
        Exercise("doorway row", "position yourself into a semi"
                 " squat so you are facing a door frame. grab onto the door frame"
                 " with one hand, and pull yourself into the door frame. slowly"
                 " extend your arm again to return to the starting position.",
                 "back"));
    exercise_vec_.emplace_back(
        Exercise("full bridge", "start by lying with your back"
                 " on the ground. place your hands beside your head and turn so"
                 " your fingers point towards your feet. bring your hips up as you"
                 " round your back, while continuously squeezing your butt and leg"
                 " muscles. hold this position.", "back"));
    exercise_vec_.emplace_back(
        Exercise("reverse snow angels", "pretend to make snow"
                 " angels, but laying with your stomach on the ground. make sure"
                 " your arms and legs are not touching the ground.",
                 "back"));
    exercise_vec_.emplace_back(
        Exercise("bird dogs", "go on all fours, with your back"
                 " parallel to the ground. simultaneously raise your left arm"
                 " and your right leg, extended them outwards. lower back to the"
                 " ground, and alternate.", "back"));
  }

  if (FLAGS_chest) {
    exercise_vec_.emplace_back(
        Exercise("negative push ups", "start in the push up"
                 " position, and lower yourself until your chest is just above"
                 " the ground. at this point, let your knees drop, and extend"
                 " your arms, pushing yourself back up. lift your knees off the"
                 " ground and repeat.", "chest"));
    exercise_vec_.emplace_back(
        Exercise("no arm push up", "get into a plank position,"
                 " keeping your forearms on the ground. pretend to do a push up,"
                 " but with only your chest/back.", "chest"));
    exercise_vec_.emplace_back(
        Exercise("isometric chest squeezes", "press your hands"
                 " together, at the bottom of the palms of your hands. bend your"
                 " arms at a 90 degree angle, contracting your chest the entire"
                 " time. hold this position, then slowly return to the starting"
                 " position, relieving some of the tension along the way.",
                 "chest"));
    exercise_vec_.emplace_back(
        Exercise("push back push up", "start out in traditional"
                 " push up position. instead of pushing up on the return, push"
                 " straight back, so your knees bend and your butt is above your"
                 " ankles.", "chest"));
    exercise_vec_.emplace_back(
        Exercise("rotational push ups", "perform a normal push"
                 " up, but on the way up, rotate your body so it faces one"
                 " direction. extend your arm straight out, to form a T frame."
                 " return to the starting position and alternate.",
                 "chest"));
  }

  if (FLAGS_core) {
    exercise_vec_.emplace_back(
        Exercise("crunches", "laying with your back on the"
                 " ground and your knees bent, curl your torso up until your"
                 " shoulder blades are off the floor.", "core"));
    exercise_vec_.emplace_back(
        Exercise("bear crawl", "get into the crawl position,"
                 " with your knees off the ground. as you move your left hand"
                 " forward, move your right leg forward as well. alternate until"
                 " you can't go any further.", "core"));
    exercise_vec_.emplace_back(
        Exercise("v ups", "lay on the floor, and lift your legs"
                 " straight up and your upper body up as well until you achieve"
                 " a v shape.", "core"));
    exercise_vec_.emplace_back(
        Exercise("sit up", "lie on your back, with your knees"
                 " bent and hands crossed over your chest. lift your upper body"
                 " until you are sitting straight up. gently return to the"
                 " ground.", "core"));
    exercise_vec_.emplace_back(
        Exercise("plank", "get into the push up position, but"
                 " with your forearms on the ground instead of your hands."
                 " squeeze your glutes and tighten your abdominals.",
                 "core"));
  }

  if (FLAGS_legs) {
    exercise_vec_.emplace_back(
        Exercise("squats", "stand with your head facing forward"
                 " and your chest held up and out, and your feet shoulder width"
                 " apart. sit down like your sitting into an imaginary chair."
                 " lower until your thighs are parallel to the floor, and return"
                 " to the starting position.", "legs"));
    exercise_vec_.emplace_back(
        Exercise("pistol squats", "stand with your feet shoulder"
                 " width apart, and lift one leg in front of you. bend your knee"
                 " and lower your hips back until as low as possible. return to"
                 " the starting position and alternate.", "legs"));
    exercise_vec_.emplace_back(
        Exercise("calf raises", "stand with your feet shoulder"
                 " width apart. raise your heels off the floor and squeeze your"
                 " calves. slowly return to the starting position.",
                 "legs"));
    exercise_vec_.emplace_back(
        Exercise("lunges", "stand with your feet shoulder width"
                 " apart. take a step forward and slowly bend both knees, until"
                 " the back knee is barely above the ground. return to the"
                 " starting position and alternate.", "legs"));
    exercise_vec_.emplace_back(
        Exercise("elevated glute bridges", "lie face up on the"
                 " floor, with your knees bent and feet resting on an elevated"
                 " surface. lift your hips off the ground until your knees to"
                 " your shoulders form a straight line. return to the starting"
                 " position.", "legs"));
  }

  if (FLAGS_shoulders) {
    exercise_vec_.emplace_back(
        Exercise("push ups", "get down on all fours, with"
                 " your legs fully extended. place your hands slightly wider"
                 " than shoulder width. lower yourself until your chest is just"
                 " above the ground. return to the starting position.",
                 "shoulders"));
    exercise_vec_.emplace_back(
        Exercise("pike push ups", "get into an A frame position,"
                 " keeping your head in between your arms. lower the top of your"
                 " head slowly while bending your elbows. push yourself back up.",
                 "shoulders"));
    exercise_vec_.emplace_back(
        Exercise("maltese push ups", "get into push up position,"
                 " but with your hands the opposite way. balance your torso upon"
                 " your hands while placing them just above hip level. lower"
                 " yourself to the ground, and push back up.",
                 "shoulders"));
    exercise_vec_.emplace_back(
        Exercise("wall walk", "begin in the push up position,"
                 " with your feet against the wall. slowly walk your feet up the"
                 " wall while concurrently bringing your hands closer to the wall."
                 " Continue to a height that feels safe, then slowly walk yourself"
                 " back down.", "shoulders"));
    exercise_vec_.emplace_back(
        Exercise("static handstand", "kick yourself up onto your"
                 " hands, and balance your weight while keeping your body"
                 " straight. practice next to a wall if needed.",
                 "shoulders"));
  }

  current_exercise_ = exercise_vec_.front();
}

void MyApp::update() {
  const auto time = system_clock::now();

  if (state_ == State::kContinue) {
    if (timer_.isStopped()) {
      timer_.resume();
    }

    const auto time_since_switch = time - last_switch_;
    if (time_since_switch > seconds(kTimeForExercise)) {
      last_switch_ = time;
      timer_.start(0);
      if (exercise_index_ != exercise_vec_.size() - 1) {
        ++exercise_index_;
        current_exercise_ = exercise_vec_.at(exercise_index_);
      }
      if (exercise_index_ == exercise_vec_.size() - 1) {
        state_ = State::kFinished;
      }
    }
  }

  if (state_ == State::kFinished) {
    timer_.stop();
    if (!added_to_past_workouts_) {
      workout::WorkoutsDatabase workout_database(
          "C:\\Users\\Owen Michuda\\Downloads\\cinder_0.9.2_vc2015\\"
          "cinder_0.9.2_vc2015\\my-projects\\final-project\\assets\\"
          "past_workouts.db");
      workout_database.AddWorkoutToDatabase(plan_);
      added_to_past_workouts_ = true;
    }
  }

  if (state_ == State::kPaused) {
    timer_.stop();
  }
}

void MyApp::DrawBackground() {
  // Light blue
  cinder::gl::clear(kLightBlue);
}

auto GetTextBox(const string& text, const Color& color, const Font& font)
    -> TextBox {
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
  int current_second = static_cast<int>(kTimeForExercise) -
                       static_cast<int>(timer_.getSeconds());
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
void MyApp::DrawFinish() {
  const string finish_message = "Congratulations! You have completed your workout."
      " Judging on your last few workouts, you should work on theses areas next:";
  const Font finish_font = Font("Papyrus", 100);
  TextBox finish_tbox = TextBox()
      .alignment(TextBox::CENTER)
      .font(finish_font)
      .size(getWindowSize().x * (0.75), TextBox::GROW)
      .color(kWhite)
      .backgroundColor(cinder::ColorA(0, 0, 0, 0))
      .text(finish_message);
  TextureRef finish_texture = cinder::gl::Texture2d::create(finish_tbox.render());

  const float finish_tbox_x = finish_tbox.measure().x;
  const float finish_tbox_y = finish_tbox.measure().y;
  const ivec2 finish_loc = {getWindowCenter().x - finish_tbox_x / 2,
                            getWindowCenter().y * (0.5) - finish_tbox_y / 2};

  cinder::gl::draw(finish_texture, finish_loc);

  workout::WorkoutsDatabase workout_database(
      "C:\\Users\\Owen Michuda\\Downloads\\cinder_0.9.2_vc2015\\"
      "cinder_0.9.2_vc2015\\my-projects\\final-project\\assets\\"
      "past_workouts.db");
  const vector<string> recommended_workouts = workout_database.RecommendedWorkout();

  int count = 0;
  for (string workout : recommended_workouts) {
    TextBox exercises_tbox =
        GetTextBox(workout, kWhite, finish_font);
    TextureRef exercises_texture =
        cinder::gl::Texture2d::create(exercises_tbox.render());

    const float exercises_tbox_x = exercises_tbox.measure().x;
    const float exercises_tbox_y = exercises_tbox.measure().y;
    const ivec2 exercises_loc = {getWindowCenter().x - exercises_tbox_x / 2,
                                 getWindowCenter().y - (exercises_tbox_y / 2) + (count * exercises_tbox_y)};

    cinder::gl::draw(exercises_texture, exercises_loc);
    ++count;
  }
}

void MyApp::draw() {
  DrawBackground();

  if (state_ == State::kContinue || state_ == State::kPaused) {
    DrawTimer();
    DrawText();
  }

  if (state_ == State::kFinished) {
    DrawFinish();
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_SPACE: {
      if (state_ == State::kContinue) {
        state_ = State::kPaused;
        break;
      }
      if (state_ == State::kPaused) {
        state_ = State::kContinue;
        break;
      }
    }
  }
}

}  // namespace myapp
