#include "Asteroids.h"

Asteroids::Asteroids(Vector2f position, int speed)
{
	is_alive = true;
	radius = ASTER_RADIUS;
	type = LARGE;
	angle = rand() % 360;
	this->speed = speed;
	velocity = Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
	asteroid_texture.loadFromFile(ASTER_IMAGE_PATH);
	expo_sound_bf.loadFromFile(ASTER_EXPO_SOUND);
	expo_sound.setBuffer(expo_sound_bf);
	asteroid.setTexture(&asteroid_texture);
	asteroid.setRadius(radius);
	asteroid.setOrigin(Vector2f(radius, radius));
	asteroid.setPosition(position);
	asteroid.setRotation(angle);
	asteroid.setOutlineThickness(2);
}

Asteroids::Asteroids(Vector2f pos, float radius, float angle, int type, int speed)
{
	is_alive = true;
	this->radius = radius;
	this->angle = angle;
	this->type = type;
	this->speed = speed;
	velocity = Vector2f(cos(angle * DEGTORAD), sin(angle * DEGTORAD));
	asteroid_texture.loadFromFile(ASTER_IMAGE_PATH);
	asteroid.setTexture(&asteroid_texture);
	asteroid.setRadius(radius);
	asteroid.setOrigin(Vector2f(radius, radius));
	asteroid.setPosition(position);
	asteroid.setRotation(angle);

}

void Asteroids::draw(RenderWindow& window)
{
	window.draw(asteroid);
}

void Asteroids::move(Time dt)
{
	Vector2f distance = velocity * speed * dt.asSeconds();
	asteroid.move(distance);
	Vector2f pos = asteroid.getPosition();
	if (pos.x > WINDOWWIDTH) pos.x = 0;
	if (pos.y > WINDOWHEIGHT) pos.y = 0;
	if (pos.x < 0) pos.x = WINDOWWIDTH;
	if (pos.y < 0) pos.y = WINDOWHEIGHT;
	asteroid.setPosition(pos);
}



void Asteroids::takeDamage(std::vector<Asteroids>& new_asteroids, int& scoreCount)
{
	//expo_sound.play();
	is_alive = false;
	scoreCount += 10;
	Vector2f pos = asteroid.getPosition();
	if (type != SMALL) {
		//new two asteroids
		Asteroids *a1 = new Asteroids(Vector2f(pos.x - 5, pos.y + 5), radius / 2, rand() % 360, type - 1, speed + 1);
		new_asteroids.push_back(*a1);
		Asteroids* a2 = new Asteroids(Vector2f(pos.x - 5, pos.y - 5), radius / 2, rand() % 360, type - 1, speed + 1);
		new_asteroids.push_back(*a2);
	}
}

bool Asteroids::isAlive()
{
	return is_alive;
}

void Asteroids::play()
{
	expo_sound.play();
}

int Asteroids::getType()
{
	return type;
}



