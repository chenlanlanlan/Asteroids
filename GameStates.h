#pragma once
#include "Define.h"

using namespace sf;

class GameStates
{
public :
	GameStates(const String& item1, const String& item2, int gameState);
	void setText(Text& txt, int fontSize, Vector2f pos, String str, Color color);
	void draw(RenderWindow& window, Vector2f titlePos, String title);
	void getEventFromUser(RenderWindow& window, int& gameState, bool& isFromGAMEOVER);

private:
	int selevtedItemIndex;
	Text list[2];
	FloatRect txtR1, txtR2;
	Font font;
	SoundBuffer sound_bf;
	Sound sound;
	int gameState;
	void handleKeyboardInput(RenderWindow& window, Keyboard::Key event, int& gameState, bool& isFromGAMEOVER);
	void handleMouseMove(Event::MouseMoveEvent mouse);
	void handleMouseButton(RenderWindow& window, Mouse::Button button, int& gameState, bool& isFromGAMEOVER);
	void setGameState(RenderWindow& window, int& gameState, bool &isFromGAMEOVER);
	void selectStart();
	void selectQuit();

};

