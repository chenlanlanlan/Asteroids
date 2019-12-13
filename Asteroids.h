#pragma once
#include "Define.h"
class Asteroids
{
public:
	CircleShape asteroid;
	Vector2f velocity;
	bool is_alive;
	Asteroids(Vector2f position, int speed, int index);
	Asteroids(Vector2f pos, float radius,float angle, int type, int speed, Vector2f vel, int index);
	void draw(RenderWindow& window);
	void move(Time dt);
	void takeDamage(std::vector<Asteroids>& new_asteroids, int& scoreCount);
	bool isAlive();
	void play();
	int getType();
	void reverse();
	int getIndex();
	void setVelocity(float x, float y);
private:
	int type, index;
	Vector2f position, origin;
	Texture asteroid_texture;
	SoundBuffer expo_sound_bf;
	Sound expo_sound;
	float radius, angle, speed;
};

