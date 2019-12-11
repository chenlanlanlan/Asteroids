#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>

//for game class
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600
#define BIGFONTSIZE 36
#define MIDFONTSIZE 24
#define SMLFONTSIZE 16
#define PLAYERLIFE 3
#define PLAYERINITIALSCORE 0;

//for ship class
#define SHIP_SPEED 200.F
#define SHIP_RADIUS 25.F
#define DEGTORAD 0.017454
#define PI 3.1415926535
#define ROTATE_SPEED 500.f
#define MAX_SPEED 800.f

#define BG_PATH "images/bg.png"
#define SHIP_IMAGE1_PATH "images/plane1.png"
#define SHIP_IMAGE2_PATH "images/plane.png"
#define SHIP_EXP_IMAGE_PATH "images/ship_exp.png"
#define BULLET_IMAGE_PATH "images/bullet.png"
#define ASTER_EXP_IMAGE_PATH "images/aster_exp.png"
#define NORMAL_ASTER_IMAGE_PATH "images/aster.png"

#define FONT_PATH "assets/KenPixel Square.ttf"

#define START_SOUND_PATH "assets/launch1.wav"
#define EXPO_SOUND_PATH "assets/beat1.wav"
#define THRUST_SOUND_PATH "assets/thrust.wav"


enum states { MENU, PLAYING, NEXTLEVEL, GAMEOVER };