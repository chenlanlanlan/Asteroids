#pragma once
#include "Define.h"
#include "GameStates.h"
#include "Ship.h"

using namespace sf;

class Game
{
public:
	Game();
	void run();

private:
	RenderWindow game_window;
	Texture bg_texture;
	Sprite bg;
	Font font;
	Text gameTitle, instruction, lifeTitle, life, scoreTitle, score, winMsg, lostMsg;
	SoundBuffer lostLifeSound_bf;
	Sound lostLifeSound;
	CircleShape shape;
	Clock clock;
	//Menu menu;
	GameStates gameMenu, gameOver;
	Ship player;
	int gameState;
	int lifeCount, scoreCount;

	void getEventFromUser(Time dt);
	void setTextureFile();
	void setText(Text& txt, int fontSize, Vector2f pos, String str);
	void initialStates();
	void configUI();
	void render();
};


