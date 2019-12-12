#include "Ship.h"

Ship::Ship()
{
	resetShip();
	thrust = false;
	ship_texture1.loadFromFile(SHIP_IMAGE1_PATH);
	ship_texture2.loadFromFile(SHIP_IMAGE2_PATH);
	ship_exp_texture.loadFromFile(SHIP_EXP_IMAGE_PATH);
	ship_thurst.loadFromFile(THRUST_SOUND_PATH);
	ship_expo.loadFromFile(THRUST_SOUND_PATH);
	radius = SHIP_RADIUS;
	ship.setRadius(radius);
	ship.setOrigin(Vector2f(radius, radius));
	ship.setPosition(position);
	ship.setTexture(&ship_texture1);
	expo_sound.setBuffer(ship_expo);
	thurst_sound.setBuffer(ship_thurst);
}

void Ship::drawShip(RenderWindow& window)
{
	window.draw(ship);
}

void Ship::handleUserInput(Time dt, Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		degree = -2;
		moveShip(dt);
	break;
	case sf::Keyboard::Right:
		//ship turn right
		degree = 2;
		moveShip(dt);
	break;
	case sf::Keyboard::Up:
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{	//ship thrust
			ship.setTexture(&ship_texture2);  
			thurst_sound.play();
			thrust = true;
			speed = SHIP_SPEED;
		}
		else
			ship.setTexture(&ship_texture1);
			thrust = false;
	break;
	}
}

void Ship::update(Time dt)
{
	if(!thrust)
		speed -= 0.5;
	if (speed <= 0) {
		speed = 0;
	}
	degree = ship.getRotation() - 90;
	velocity.x += cos(degree * DEGTORAD);
	velocity.y += sin(degree * DEGTORAD);
	normalized(velocity);

	position.x +=  velocity.x * dt.asSeconds() * speed;
	position.y +=  velocity.y * dt.asSeconds() * speed;
	if (position.x > WINDOWWIDTH) position.x = 0;
	if (position.y > WINDOWHEIGHT) position.y = 0;
	if (position.x < 0) position.x = WINDOWWIDTH;
	if (position.y < 0) position.y = WINDOWHEIGHT;
	ship.setPosition(position);
}

void Ship::moveShip(Time dt)
{
	if (!thrust) { //not moving, turn left without changing position		
		ship.rotate(degree * ROTATE_SPEED * dt.asSeconds());
	}
	else {
		ship.rotate(degree * ROTATE_SPEED * dt.asSeconds());
		update(dt);
	}
}

void Ship::resetShip()
{
	velocity = Vector2f(0, 0);
	position = Vector2f(WINDOWWIDTH / 2, WINDOWHEIGHT / 2); //center
	speed = 0;
	thrust = false;
	degree = 0;
}

void Ship::normalized(Vector2f& vec)
{
	vec.x = vec.x / sqrtf(vec.x * vec.x + vec.y * vec.y);
	vec.y = vec.y / sqrtf(vec.x * vec.x + vec.y * vec.y);
}

void Ship::destoryShip()
{
	ship.setTexture(&ship_exp_texture);
	expo_sound.play();
}
