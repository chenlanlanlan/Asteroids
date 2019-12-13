#pragma once
#include "Define.h"
class Asteroids
{
public:
	CircleShape asteroid;
	bool is_alive;
	Asteroids(Vector2f position, int speed);
	Asteroids(Vector2f pos, float radius,float angle, int type, int speed);
	void draw(RenderWindow& window);
	void move(Time dt);
	void takeDamage(std::vector<Asteroids>& new_asteroids, int& scoreCount);
	bool isAlive();
	void play();
	int getType();

private:
	int type;
	Vector2f velocity, position, origin;
	Texture asteroid_texture;
	SoundBuffer expo_sound_bf;
	Sound expo_sound;
	float radius, angle, speed;
};

