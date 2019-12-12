#pragma once
#include "Define.h"


using namespace sf;

class Ship
{
public:
	CircleShape ship;
	float speed;
	Sound expo_sound;
	Ship();
	void drawShip(RenderWindow &window);
	void handleUserInput(Time dt, Keyboard::Key key);
	void update(Time dt);
	void resetShip();
	void destoryShip();

private:
	Vector2f velocity, position, origin;
	Texture ship_texture1, ship_texture2, ship_exp_texture;
	SoundBuffer ship_expo;
	SoundBuffer ship_thurst;
	Sound thurst_sound;
	float radius, degree;
	bool thrust;
	void moveShip(Time dt);
	void normalized(Vector2f& direction);
};

