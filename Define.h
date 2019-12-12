#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "Ship.h"
#include "Bullet.h"
#include "Asteroids.h"

//for game class
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600
#define BIGFONTSIZE 36
#define MIDFONTSIZE 24
#define SMLFONTSIZE 16
#define PLAYERLIFE 3
#define PLAYERINITIALSCORE 0;

//for ship class
#define SHIP_SPEED 100.f
#define SHIP_RADIUS 25.f
#define DEGTORAD 0.017454
#define PI 3.1415926535
#define ROTATE_SPEED 500.f

//for bullet class
#define LIFETIME 1000.f
#define BULLET_SPEED 0.9f
#define BULLETWIDTH 5.f
#define BULLETHEIGHT 20.f

//for Asteroid class
#define ASTER_SPEED 30.f;
#define ASTER_RADIUS 60.f;


#define BG_PATH "images/bg.png"
#define SHIP_IMAGE1_PATH "images/plane1.png"
#define SHIP_IMAGE2_PATH "images/plane.png"
#define SHIP_EXP_IMAGE_PATH "images/ship_exp.png"
#define BULLET_IMAGE_PATH "images/bullet.png"
#define ASTER_EXP_IMAGE_PATH "images/aster_exp.png"
#define ASTER_IMAGE_PATH "images/aster.png"

#define FONT_PATH "assets/KenPixel Square.ttf"

#define START_SOUND_PATH "assets/launch1.wav"
#define EXPO_SOUND_PATH "assets/beat1.wav"
#define THRUST_SOUND_PATH "assets/thrust.wav"
#define FIRE_SOUND_PATH "assets/fire.wav"

enum states { MENU, PLAYING, NEXTLEVEL, GAMEOVER };