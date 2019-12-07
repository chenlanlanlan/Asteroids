#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600
#define BIGFONTSIZE 36
#define MIDFONTSIZE 24
#define SMLFONTSIZE 16
#define SHIP_START_POS_X 

#define BG_PATH "images/bg.png"
#define SHIP_IMAGE_PATH "images/plane.png"
#define SHIP_IMAGE_PATH "images/bullet.png"
#define SHIP_IMAGE_PATH "images/aster_exp.png"
#define SHIP_IMAGE_PATH "images/aster.png"
#define FONT_PATH "assets/KenPixel Square.ttf"
#define FIRE_SOUND_PATH "launch1.wav"


enum states { MENU, PLAYING, NEXTLEVEL, GAMEOVER };