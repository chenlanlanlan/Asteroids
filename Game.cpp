#include "Game.h"
#include<iostream>

Game::Game() : gameMenu("START GAME", "QUIT GAME", MENU),
gameOver("BACK TO MENU", "QUIT GAME", GAMEOVER),
game_window(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Asteroids"),
clock(),
font(),
player()
{
	game_window.setVerticalSyncEnabled(true);
	game_window.setFramerateLimit(60);
	setTextureFile();
	font.loadFromFile(FONT_PATH);
	initialStates();
	configUI();
	gameState = MENU;
}

void Game::run()
{
	while (game_window.isOpen())
	{
		Time dt = clock.restart();
		switch (gameState) {
		case MENU:
			gameMenu.getEventFromUser(game_window, gameState);
		break;
		case PLAYING:
			getEventFromUser(dt);
			player.push(dt);
			//if (lifeCount < 0) {
			//	gameState = GAMEOVER;
			//	initialStates();
			//}
		break;
		//case NEXTLEVEL:
		case GAMEOVER:
			gameOver.getEventFromUser(game_window, gameState);
		break;
		}
		//state machine
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
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				gameState = MENU;
			player.handleUserInput(dt, event.key.code);
		break;
		case Event::KeyReleased:
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				gameState = MENU;
			player.handleUserInput(dt, event.key.code);
			// handle key pressed
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
	scoreCount = PLAYERINITIALSCORE;
	lifeCount = PLAYERLIFE;
	score.setString(std::to_string(scoreCount));
	life.setString(std::to_string(lifeCount));
	player.resetShip();
}

void Game::configUI()
{
	//in game ui
	setText(scoreTitle, MIDFONTSIZE, Vector2f(100.f, 5.f), "Score: ");
	setText(score, MIDFONTSIZE, Vector2f(250.f, 5.f), std::to_string(scoreCount));
	setText(lifeTitle, MIDFONTSIZE, Vector2f(500.f, 5.f), "Life: ");
	setText(life, MIDFONTSIZE, Vector2f(650.f, 5.f), std::to_string(lifeCount));

	setText(winMsg, BIGFONTSIZE, Vector2f(350.f, 200.f), "YOU WIN! NEXT LEVEL!\nPress space or click left mouse to continue");
}

void Game::render()
{
	game_window.clear();
	//game_window.draw(shape);
	game_window.draw(bg);
	switch (gameState)
	{
	case MENU:// render start menu
		gameMenu.draw(game_window, Vector2f(120.f, 200.f), "Welcome to Asteroid !");
	break;
	
	case PLAYING:
		game_window.draw(scoreTitle);
		game_window.draw(score);
		game_window.draw(lifeTitle);
		game_window.draw(life);
		player.drawShip(game_window);

	break;
	
	case NEXTLEVEL:
		game_window.draw(winMsg);
	break;
	
	case GAMEOVER:
		game_window.draw(scoreTitle);
		game_window.draw(score);
		game_window.draw(lifeTitle);
		game_window.draw(life);
		gameOver.draw(game_window, Vector2f(270.f, 200.f), "GAME OVER!");
	break;
	}

	game_window.display();
}
