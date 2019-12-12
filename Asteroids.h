#pragma once
#include "Define.h"
class Asteroids
{
public:
	CircleShape asteroid;
	Asteroids();
	void move();

private:
	int hitCount;
	Vector2f velocity, position, origin;
	Texture asteroid_texture;
	SoundBuffer expo_sound_bf;
	Sound expo_sound;
	float radius;
};

