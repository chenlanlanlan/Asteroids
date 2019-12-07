#pragma once
#include "Define.h"
#include "GameStates.h"

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
	SoundBuffer startSound_bf, lostLifeSound_bf;
	Sound startSound, lostLifeSound;
	CircleShape shape;
	Clock clock;
	//Menu menu;
	GameStates gameMenu, gameOver;
	int gameState;
	int lifeCount, scoreCount;

	void getEventFromUser(Time dt);
	void handleKeyboardInput();
	void handleMouseInput();
	void setTextureFile();
	void setText(Text& txt, int fontSize, Vector2f pos, String str);
	void initialStates();
	void configUI();
	void render();
};


