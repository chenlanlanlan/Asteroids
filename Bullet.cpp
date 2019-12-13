#include "Bullet.h"

Bullet::Bullet(Vector2f position, float angle) : direction(cos((angle - 90) * DEGTORAD), sin((angle - 90) * DEGTORAD))
{
	bullet_texture.loadFromFile(BULLET_IMAGE_PATH);
	bullet.setTexture(&bullet_texture);
	bullet.setSize(Vector2f(BULLETWIDTH, BULLETHEIGHT)); 
	bullet.setOrigin(Vector2f(BULLETWIDTH / 2, BULLETHEIGHT / 2));
	bullet.setPosition(Vector2f(position.x, position.y));
	bullet.setRotation(angle);
	remaining_life = 0.4f;
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
	Vector2f pos = bullet.getPosition();
	if (pos.x > WINDOWWIDTH) pos.x = 0;
	if (pos.y > WINDOWHEIGHT) pos.y = 0;
	if (pos.x < 0) pos.x = WINDOWWIDTH;
	if (pos.y < 0) pos.y = WINDOWHEIGHT;
	bullet.setPosition(pos);
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



