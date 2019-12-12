#include "Bullet.h"

Bullet::Bullet(Vector2f position, float angle) : direction(cos((angle - 90) * DEGTORAD), sin((angle - 90) * DEGTORAD))
{
	bullet.setSize(Vector2f(BULLETWIDTH, BULLETHEIGHT)); 
	bullet.setOrigin(Vector2f(BULLETWIDTH / 2, BULLETHEIGHT / 2));
	bullet.setPosition(Vector2f(position.x, position.y));
	bullet.setRotation(angle);
	remaining_life = 10.f;
	speed = 1000.f;
	is_alive = true;
}

void Bullet::fire(Time time)
{
	if(!is_alive) return;
	remaining_life -= time.asSeconds();
	if (remaining_life <= 0) is_alive = false;
	Vector2f distance = direction * speed * time.asSeconds();
	bullet.move(distance);
}

void Bullet::drawBullet(RenderWindow& window)
{
	window.draw(bullet);
}

void Bullet::destoryBullet()
{
	is_alive = false;
}

bool Bullet::isAlive()
{
	return is_alive;
}



