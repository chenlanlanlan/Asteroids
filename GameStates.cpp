#include "GameStates.h"
#include <iostream>

GameStates::GameStates(const String& item1, const String& item2, int gameState)
{
	this->gameState = gameState;
	font.loadFromFile(FONT_PATH);
	setText(list[0], BIGFONTSIZE, Vector2f(250.f, 300.f), item1, Color(46, 130, 158));
	setText(list[1], BIGFONTSIZE, Vector2f(270.f, 400.f), item2, Color::White);
	selevtedItemIndex = 0;
	txtR1 = list[0].getGlobalBounds();
	txtR2 = list[1].getGlobalBounds();
	if (gameState == MENU) {
		sound_bf.loadFromFile(START_SOUND_PATH);
		sound.setBuffer(sound_bf);
	}
}

void GameStates::setText(Text& txt, int fontSize, Vector2f pos, String str, Color color)
{
	txt.setCharacterSize(fontSize);
	txt.setFont(font);
	txt.setPosition(pos);
	txt.setFillColor(color);
	txt.setString(str);
}

void GameStates::draw(RenderWindow& window, Vector2f titlePos, String title)
{
	Text titleText;
	setText(titleText, BIGFONTSIZE, titlePos, title, Color::White);
	window.draw(titleText);
	for (auto item : list) {
		window.draw(item);
	}
}

void GameStates::getEventFromUser(RenderWindow& window, int& gameState)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::KeyPressed:
			// handle key pressed
			handleKeyboardInput(window, event.key.code, gameState);
			break;
		case Event::MouseMoved:
			// handle mouse button pressed
			handleMouseMove(event.mouseMove);
			break;
		case Event::MouseButtonPressed:
			//handle mouse button pressed
			handleMouseButton(window, event.mouseButton.button, gameState);
			break;
		case Event::Closed:
			window.close();
			break;
		}
	}
}

void GameStates::selectStart()
{
	selevtedItemIndex = 0;
	list[0].setFillColor(Color(46, 130, 158)); //selected color
	list[1].setFillColor(Color::White);
}

void GameStates::selectQuit()
{
	selevtedItemIndex = 1;
	list[0].setFillColor(Color::White);
	list[1].setFillColor(Color(46, 130, 158)); //selected color
}

void GameStates::handleKeyboardInput(RenderWindow& window, Keyboard::Key event, int& gameState)
{
	switch (event)
	{
	case Keyboard::Up:
		selectStart();
		break;
	case Keyboard::Down:
		selectQuit();
		break;
	case Keyboard::Space:
		setGameState(window, gameState);
		break;
	}
}

void GameStates::handleMouseMove(Event::MouseMoveEvent mouse)
{
	if (txtR1.contains(mouse.x, mouse.y))
		selectStart();
	else if (txtR2.contains(mouse.x, mouse.y))
		selectQuit();
}

void GameStates::handleMouseButton(RenderWindow& window, Mouse::Button button, int& gameState)
{
	if (button == Mouse::Button::Left) {
		setGameState(window, gameState);
	}
}

void GameStates::setGameState(RenderWindow& window, int& gameState)
{
	switch (gameState)
	{
	case MENU:
		if (selevtedItemIndex == 0){
			sound.play();
			gameState = PLAYING;
		}
		else
			window.close();
	break;
	case GAMEOVER:
		if (selevtedItemIndex == 0)
			gameState = MENU;
		else
			window.close();
	break;
	}
}
