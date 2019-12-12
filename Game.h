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
	SoundBuffer lostLifeSound_bf, fire_sound_bf;
	Sound lostLifeSound, fire_sound;
	CircleShape shape;
	Clock clock;
	GameStates gameMenu, gameOver;
	Ship player;
	std::vector<Bullet> bullets;
	std::vector<Asteroids> asteroids;
	std::vector<Bullet>::iterator start_bullets;
	std::vector<Asteroids>::iterator start_asteroids;
	
	int gameState;
	int lifeCount, scoreCount;
	bool isPlaying;
	void getEventFromUser(Time dt);
	void setTextureFile();
	void setText(Text& txt, int fontSize, Vector2f pos, String str);
	void initialStates();
	void configUI();
	void render();
	void updateBullet(Time dt);
	void updateAsteroids(Time dt);
	void fire();
};


