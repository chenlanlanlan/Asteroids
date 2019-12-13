#include "Asteroids.h"

Asteroids::Asteroids(Vector2f position, int speed, int index)
{
	this->index = index;
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

Asteroids::Asteroids(Vector2f pos, float radius, float angle, int type, int speed, Vector2f vel, int index)
{
	this->index = index;
	is_alive = true;
	this->radius = radius;
	this->angle = angle;
	this->type = type;
	this->speed = speed;
	if (vel.x * cos(angle * DEGTORAD) >= 0) 
		velocity.x = -cos(angle * DEGTORAD);
	else
		velocity.x = cos(angle * DEGTORAD);
	if (vel.y * sin(angle * DEGTORAD) >= 0) 
		velocity.y = -sin(angle * DEGTORAD);
	else
		velocity.y = sin(angle * DEGTORAD);
	
	asteroid_texture.loadFromFile(ASTER_IMAGE_PATH);
	asteroid.setTexture(&asteroid_texture);
	asteroid.setRadius(radius);
	asteroid.setOrigin(Vector2f(radius, radius));
	asteroid.setPosition(pos);
	asteroid.setRotation(angle);
	asteroid.setOutlineThickness(2);
}

void Asteroids::draw(RenderWindow& window)
{
	window.draw(asteroid);
}

void Asteroids::move(Time dt)
{
	//normolize velocity
	float mag = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
	Vector2f normolized = Vector2f(velocity.x / mag, velocity.y / mag);

	std::cout << "this_vel: " <<index << " : "<< normolized.x << ", " << normolized.y << std::endl;

	Vector2f distance = normolized * speed * dt.asSeconds();
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
	//float angle = asteroid.getRotation();
	if (type != SMALL) {
		//new two asteroids
		Asteroids *a1 = new Asteroids(Vector2f(pos.x - radius/2, pos.y - radius / 2), radius / 2, rand() % 360, type - 1, speed + 2, velocity, new_asteroids.size()+1);
		new_asteroids.push_back(*a1);
		Asteroids* a2 = new Asteroids(Vector2f(pos.x - radius / 2, pos.y + radius / 2), radius / 2, rand() % 360, type - 1, speed + 2, velocity, new_asteroids.size() + 1);
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

void Asteroids::reverse()
{
	std::cout << "Reverce!";
	
}

int Asteroids::getIndex()
{
	return index;
}

void Asteroids::setVelocity(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}





