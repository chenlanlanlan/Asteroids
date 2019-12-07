#pragma once
#include "Define.h"

using namespace sf;

class GameStates
{
public :
	GameStates(const String& item1, const String& item2, int gameState);
	void setText(Text& txt, int fontSize, Vector2f pos, String str, Color color);
	void draw(RenderWindow& window, Vector2f titlePos, String title);
	void getEventFromUser(RenderWindow& window, int& gameState);

private:
	int selevtedItemIndex;
	Text list[2];
	FloatRect txtR1, txtR2;
	Font font;
	int gameState;
	void handleKeyboardInput(RenderWindow& window, Keyboard::Key event, int& gameState);
	void handleMouseMove(Event::MouseMoveEvent mouse);
	void handleMouseButton(RenderWindow& window, Mouse::Button button, int& gameState);
	void setGameState(RenderWindow& window, int& gameState);
	void selectStart();
	void selectQuit();

};

