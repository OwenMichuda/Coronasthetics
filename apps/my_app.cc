// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <C:\Users\Owen Michuda\Downloads\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project\cmake-build-debug\_deps\gflags-build\include\gflags\gflags.h>
#include "../cmake-build-debug/_deps/gflags-build/include/gflags/gflags.h"

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

DECLARE_bool(arms);
DECLARE_bool(shoulders);
DECLARE_bool(chest);
DECLARE_bool(core);
DECLARE_bool(back);
DECLARE_bool(legs);

MyApp::MyApp()
    : plan_(FLAGS_arms,
        FLAGS_shoulders,
        FLAGS_chest,
        FLAGS_core,
        FLAGS_back,
        FLAGS_legs) {}

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() {
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
