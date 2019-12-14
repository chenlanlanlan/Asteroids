#include "Game.h"
#include<iostream>

Game::Game() : gameMenu("START GAME", "QUIT GAME", MENU),
gameOver("BACK TO MENU", "QUIT GAME", GAMEOVER),
game_window(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Asteroids"),
clock(), font(), player()
{
	game_window.setVerticalSyncEnabled(true);
	game_window.setFramerateLimit(60);
	setTextureFile();
	font.loadFromFile(FONT_PATH);
	initialStates();
	gameState = MENU;
	bullets.clear();
	isProtected = isFromGAMEOVER = false;
	protectedTime = 5.f;
	designLevel(level);
}

void Game::run()
{
	while (game_window.isOpen())
	{
		std::vector<Asteroids> new_asteroids;
		Time dt = clock.restart();

		switch (gameState) {
		case MENU:
			if (lifeCount <= 0) {
				std::cout << "level: " << level << std::endl;
				player.resetShip();
				initialStates();
				designLevel(level);
				std::cout << "level: " << level << std::endl;
				break;
			}
			gameMenu.getEventFromUser(game_window, gameState, isFromGAMEOVER);
		break;
		case PLAYING:
			std::cout << "size: " << asteroids.size() << std::endl;
			getEventFromUser(dt);
			player.update(dt);
			bullet_aster_collision(new_asteroids, scoreCount);

			updateAsteroids(dt);
			updateBullet(dt);
			if (lifeCount < 0) {
				gameState = GAMEOVER;
				lostLifeSound.play();
				break;
			}
			protectedTime -= dt.asSeconds();
			if (protectedTime - dt.asSeconds() <= 0) {
				isProtected = false;
				protectedTime = 5.f;
			}
			player.ship.setOutlineThickness(0);
			//player.ship.setOutlineColor(Color::White);
			if (!isProtected)	ship_aster_collision();
			if (asteroids.size() == 0 && scoreCount != 0) gameState = NEXTLEVEL;
		break;
		case NEXTLEVEL:
			getEventFromUser(dt);
			fire_sound.play();
		break;
		case GAMEOVER:
			gameOver.getEventFromUser(game_window, gameState, isFromGAMEOVER);
		break;
		}
		render();
	}
}

void Game::getEventFromUser(Time dt)
{
	sf::Event event;
	while (game_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			game_window.close();
		break;
		case Event::KeyPressed:			// handle key pressed
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				gameState = MENU;
				initialStates();
				designLevel(level);
			}
			player.handleUserInput(dt, event.key.code);
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (gameState == NEXTLEVEL) {
					designLevel(level++);
					gameState = PLAYING;
				}
				fire();
			}
		break;
		case Event::KeyReleased:
			player.handleUserInput(dt, event.key.code);
			// handle key Released
		break;
		case Event::MouseButtonPressed:
			// handle mouse button pressed
		break;
		case Event::MouseMoved:
			// handle mouse button pressed
		break;
		} 
	}
}

void Game::setTextureFile()
{
	bg_texture.loadFromFile(BG_PATH);
	bg_texture.setSmooth(true);
	bg.setTexture(bg_texture);
	fire_sound_bf.loadFromFile(FIRE_SOUND_PATH);
	fire_sound.setBuffer(fire_sound_bf);
}

void Game::setText(Text& txt, int fontSize, Vector2f pos, String str)
{
	txt.setCharacterSize(fontSize);
	txt.setFont(font);
	txt.setPosition(pos);
	txt.setFillColor(Color::White);
	txt.setString(str);
}

void Game::initialStates()
{
	srand(time(NULL));
	level = 5;
	scoreCount = 0;
	lifeCount = 3;
	player.resetShip();
	asteroids.clear();
	configUI();
}

void Game::configUI()
{
	//in game ui
	setText(scoreTitle, MIDFONTSIZE, Vector2f(100.f, 5.f), "Score: ");
	setText(score, MIDFONTSIZE, Vector2f(250.f, 5.f), std::to_string(scoreCount));
	setText(lifeTitle, MIDFONTSIZE, Vector2f(500.f, 5.f), "Life: ");
	setText(life, MIDFONTSIZE, Vector2f(650.f, 5.f), std::to_string(lifeCount));
	setText(winMsg, BIGFONTSIZE, Vector2f(20.f, 200.f), "YOU WIN! NEXT LEVEL!\nPress space to continue");
}

void Game::renderUI()
{
	game_window.draw(scoreTitle);
	score.setString(std::to_string(scoreCount));
	game_window.draw(score);
	game_window.draw(lifeTitle);
	life.setString(std::to_string(lifeCount));
	game_window.draw(life);
}

void Game::render()
{
	game_window.clear();
	game_window.draw(bg);
	switch (gameState)
	{
	case MENU:// render start menu
		gameMenu.draw(game_window, Vector2f(120.f, 200.f), "Welcome to Asteroid !");
	break;
	
	case PLAYING:
		if (isProtected) player.ship.setFillColor(Color::Red);
		else player.ship.setFillColor(Color::White);
		player.drawShip(game_window);
		for (auto aster : asteroids)
			aster.draw(game_window);
		for (Bullet bul : bullets)
			bul.drawBullet(game_window);
		renderUI();
	break;
	
	case NEXTLEVEL:
		game_window.draw(winMsg);
		renderUI();
	break;
	
	case GAMEOVER:
		gameOver.draw(game_window, Vector2f(270.f, 200.f), "GAME OVER!");
		renderUI();
	break;
	}
	game_window.display();
}

void Game::updateBullet(Time dt)
{
	start_bullets = bullets.begin();
	while (start_bullets != bullets.end()) {
		if (start_bullets->isAlive()) {
			start_bullets->fire(dt);
			++start_bullets;
		}
		else 
			start_bullets = bullets.erase(start_bullets);
	}
}

void Game::updateAsteroids(Time dt)
{
	//asters_collision();
	start_asteroids = asteroids.begin();
	while (start_asteroids != asteroids.end()) {
		if (start_asteroids->isAlive()) {
			start_asteroids->move(dt);
			++start_asteroids;
		}
		else
			start_asteroids = asteroids.erase(start_asteroids);
	}
}

void Game::fire()
{
	fire_sound.play();
	if (bullets.size() >= 10) bullets.clear();
	Bullet* b = new Bullet(player.ship.getPosition(), player.ship.getRotation());
	bullets.push_back(*b);
}

void Game::designLevel(int level)
{
	std::cout << "Hey!" << std::endl;
	srand(time(NULL));
	for (int i = 1; i <= level; i++) {
		Vector2f pos = Vector2f(0 + rand() % (WINDOWWIDTH + 0 - 1), 0 + rand() % (WINDOWHEIGHT + 0 - 1));
		Asteroids* aster = new Asteroids(pos, ASTER_SPEED + level - 3, i);
		asteroids.push_back(*aster);
	}
}

bool Game::isShipCollidewithAster(CircleShape s1, CircleShape s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

bool Game::isBulletCollidewithAster(RectangleShape s1, CircleShape s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

void Game::bullet_aster_collision(std::vector<Asteroids>& new_asteroids, int& scoreCount)
{
	start_asteroids = asteroids.begin();
	while (start_asteroids != asteroids.end()) {
		start_bullets = bullets.begin();
		while (start_bullets != bullets.end()) {
			if (!start_bullets->isAlive()) {
				++start_bullets;
				continue;
			}
			if (isBulletCollidewithAster(start_bullets->bullet, start_asteroids->asteroid)) {
				start_bullets->destoryBullet();
				start_asteroids->play();
				start_asteroids->takeDamage(new_asteroids, scoreCount);
				break;
			}
			++start_bullets;
		}
		++start_asteroids;
	}
	asteroids.insert(asteroids.end(), new_asteroids.begin(), new_asteroids.end());
}

void Game::ship_aster_collision()
{
	start_asteroids = asteroids.begin();
	while (start_asteroids != asteroids.end()) {
		if (isShipCollidewithAster(player.ship, start_asteroids->asteroid)) {
			//player got hit
			lifeCount = lifeCount - 1;
			player.destoryShip();
			//reset the ship
			isProtected = true;
			player.resetShip();
		}
		++start_asteroids;
	}
}

void Game::asters_collision()
{
	Vector2f offset;
	for (auto& a : asteroids) {
		for (auto& target : asteroids) {
			Vector2f pos1 = a.asteroid.getPosition();
			Vector2f pos2 = target.asteroid.getPosition();
			if (a.getIndex() == target.getIndex()) break;
			if (isShipCollidewithAster(a.asteroid, target.asteroid)) {
				Vector2f offset, tmp;
				Vector2f distanceVector = pos2 - pos1; //from a  to target
				float distance = sqrtf(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
				float overlap = a.asteroid.getRadius()+3 + target.asteroid.getRadius()+3 - distance;
				// a and target exchange velocity
				Vector2f newVelocity = Vector2f(distanceVector.x / distance, distanceVector.y / distance);
				tmp = a.velocity;
				a.setVelocity(-1 * abs(target.velocity.x), -1 * abs(target.velocity.y));
				target.setVelocity(-1 * abs(tmp.x), -1 * abs(tmp.y));
				std::cout << "a_vel : " <<a.getIndex()<<" 2 : "<< a.velocity.x <<", "<<a.velocity.y  << std::endl;
				std::cout << "taget_vel : " << target.getIndex() << " 2 : " << target.velocity.x << ", " << target.velocity.y << std::endl;
				
				offset.x = newVelocity.x * (overlap / 2);
				offset.y = newVelocity.y * (overlap / 2);
				a.asteroid.move(-offset);
				target.asteroid.move(offset);
				target.asteroid.setOutlineColor(Color(255%rand(), 255%rand(), 255%rand()));
				break;
				
			}
		}
	}
}

