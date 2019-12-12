#pragma once
#include "Define.h"

using namespace sf;

class Bullet
{
public:
	RectangleShape bullet;
	Bullet(Vector2f position, float angle);
	void fire(Time time);
	void drawBullet(RenderWindow& window);
	void destoryBullet();
	bool isAlive();
private:
	bool is_alive;
	float remaining_life, speed;
	Texture bullet_texture;
	Vector2f direction;
};

