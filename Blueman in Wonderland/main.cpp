#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"MainMenu.h"
#include"GamePlay.h"
#include"Tutorials.h"
#include"LeaderBoard.h"
#include"PauseMenu.h"
#include"EnterName.h"

#define MAINMENU_S 0
#define TUTORIALS_S 1
#define LEADERBOARD_S 2
#define GAMEPLAY_S 3
#define PAUSED_S 4
#define GAMEOVER_S 5

int main() {
	srand(static_cast<unsigned>(time(NULL)));
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "BLUEMAN IN WONDERLAND", sf::Style::Close | sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	sf::Image imageIcon;
	imageIcon.loadFromFile("Sprite/Icon/icon.png");
	window.setIcon(imageIcon.getSize().x, imageIcon.getSize().y, imageIcon.getPixelsPtr());
	sf::Vector2f mousePos;

	MainMenu* mainMenu = new MainMenu;
	GamePlay* gameplay = new GamePlay;
	Tutorials* tutorials = new Tutorials;
	LeaderBoard* leaderBoard = new LeaderBoard;
	PauseMenu* gamePause = new PauseMenu;
	EnterName* enterName = new EnterName;

	short state = MAINMENU_S;
	short cntPressedEscape = 0;
	short lastState = state;


	sf::Sound menuSound, gameplaySound;
	sf::SoundBuffer menuBF, gameplayBF;
	menuBF.loadFromFile("Audio/menuThemeSong.wav");
	menuSound.setBuffer(menuBF);
	menuSound.setVolume(40);
	gameplayBF.loadFromFile("Audio/gameplayTheme.wav");
	gameplaySound.setBuffer(gameplayBF);
	gameplaySound.setVolume(20);
	bool isMenuSound = false;
	bool isGamePlay = false;

	while (window.isOpen()) {

		if (state == GAMEPLAY_S) {
			gameplay->beforeOnEvent();
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					if (state == GAMEPLAY_S) {
						++cntPressedEscape;
						if (cntPressedEscape == 1) {
							//gameplaySound.stop();
							gameplaySound.pause();
							lastState = state;
							state = PAUSED_S;
						}
					}
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape) {
					cntPressedEscape = 0;
				}
			}
			if (event.type == sf::Event::MouseMoved) {
				mousePos.x = event.mouseMove.x;
				mousePos.y = event.mouseMove.y;
			}
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left) {
					if (state == MAINMENU_S) {
						if (mainMenu->play.getFillColor() == sf::Color::Yellow) {
							state = GAMEPLAY_S;
							delete mainMenu;
							mainMenu = new MainMenu;
							mousePos = { 0.0f, 0.0f };
						}
						else if (mainMenu->exit.getFillColor() == sf::Color::Yellow) {
							window.close();
						}
						else if (mainMenu->tutorials.getFillColor() == sf::Color::Yellow) {
							lastState = state;
							state = TUTORIALS_S;
							mousePos = { 0.0f, 0.0f };
						}
						else if (mainMenu->leaderboard.getFillColor() == sf::Color::Yellow) {
							lastState = state;
							state = LEADERBOARD_S;
							delete leaderBoard;
							leaderBoard = new LeaderBoard;
							leaderBoard->setLastState(lastState);
							mousePos = { 0.0f, 0.0f };
						}
					}
					else if (state == TUTORIALS_S) {
						if (tutorials->backTxt.getFillColor() == sf::Color::Yellow) {
							state = MAINMENU_S;
							mousePos = { 0.0f, 0.0f };
						}
					}
					else if (state == LEADERBOARD_S) {
						if (leaderBoard->menuTxt.getFillColor() == sf::Color::Red) {
							lastState = state;
							state = MAINMENU_S;
							delete leaderBoard;
							leaderBoard = new LeaderBoard;
							leaderBoard->lastState = lastState;
						}
						else if (leaderBoard->playAgainTxt.getFillColor() == sf::Color::Red && lastState == GAMEOVER_S) {
							gameplaySound.play();
							lastState = state;
							state = GAMEPLAY_S;
							delete leaderBoard;
							leaderBoard = new LeaderBoard;
							leaderBoard->lastState = lastState;
						}

					}
					else if (state == PAUSED_S) {
						if (gamePause->resumeTxt.getFillColor() == sf::Color::Red) {
							gameplaySound.play();
							lastState = state;
							state = GAMEPLAY_S;
							mousePos = { 0.0f, 0.0f };
						}
						else if (gamePause->restartTxt.getFillColor() == sf::Color::Red) {
							gameplaySound.play();
							lastState = state;
							state = GAMEPLAY_S;
							delete gameplay;
							gameplay = new GamePlay;
							mousePos = { 0.0f, 0.0f };
						}
						else if (gamePause->homeTxt.getFillColor() == sf::Color::Red) {
							lastState = state;
							state = MAINMENU_S;
							delete gameplay;
							gameplay = new GamePlay;
							mousePos = { 0.0f, 0.0f };
						}
					}
					else if (state == GAMEOVER_S) {
						if (enterName->submitTxt.getFillColor() == sf::Color::Yellow && enterName->textEnterStr != "") {
							delete leaderBoard;
							leaderBoard = new LeaderBoard;
							enterName->setName(enterName->textEnterStr);
							leaderBoard->setData(enterName->getName(), enterName->getScore());
							lastState = state;
							state = LEADERBOARD_S;
							leaderBoard->setLastState(lastState);
							delete enterName;
							enterName = new EnterName;
							mousePos = { 0.0f, 0.0f };
						}
					}
				}

			if (state == GAMEOVER_S) {
				enterName->onEvent(event);
			}
			else if (state == GAMEPLAY_S) {
				gameplay->onEvent(event);
			}
		}

		if (state == GAMEPLAY_S) {
			if (gameplay->isStopPlaySound()) gameplaySound.stop();
			gameplay->afterOnEvent();
		}

		//---------------------------------------------
		if (state == MAINMENU_S) {
			mainMenu->onUpdate(mousePos);
			if (!isMenuSound) {
				menuSound.play();
				menuSound.setLoop(true);
				gameplaySound.stop();
				isMenuSound = true;
				isGamePlay = false;
			}
		}
		else if (state == TUTORIALS_S) {
			tutorials->onUpdate(mousePos);
		}
		else if (state == LEADERBOARD_S) {
			leaderBoard->onUpdate(mousePos);
		}
		else if (state == PAUSED_S) {
			gamePause->onUpdate(mousePos);
		}
		else if (state == GAMEOVER_S) {
			gameplaySound.stop();
			enterName->onUpdate(mousePos);
		}
		else if (state == GAMEPLAY_S) {
			if (!isGamePlay) {
				isGamePlay = true;
				gameplaySound.play();
				gameplaySound.setLoop(true);
				menuSound.stop();
				isMenuSound = false;
			}
			gameplay->onUpdate();

		}



		if (state == MAINMENU_S || state == LEADERBOARD_S) window.clear(sf::Color::Black);
		else if (state == GAMEPLAY_S) window.clear(sf::Color::Black);
		else if (state == TUTORIALS_S) window.clear(sf::Color(160, 75, 200, 255));
		else if (state == PAUSED_S) window.clear(sf::Color(0, 0, 0, 100));
		else if (state == GAMEOVER_S) window.clear(sf::Color::Black);
		else window.clear(sf::Color::Black);
		if (state == MAINMENU_S) {
			window.setMouseCursorVisible(1);
			mainMenu->draw(window);
		}
		else if (state == GAMEPLAY_S) {
			window.setMouseCursorVisible(0);
			gameplay->draw(window);
			if (gameplay->isVictory == 0) {
				lastState = state;
				state = GAMEOVER_S;
				enterName->engame(0, gameplay->gui->getScore());
				delete gameplay;
				gameplay = new GamePlay;
			}
			else if (gameplay->isVictory == 1) {
				lastState = state;
				state = GAMEOVER_S;
				enterName->engame(1, gameplay->gui->getScore());
				delete gameplay;
				gameplay = new GamePlay;
			}
		}
		else if (state == TUTORIALS_S) {
			window.setMouseCursorVisible(1);
			tutorials->draw(window);
		}
		else if (state == LEADERBOARD_S) {
			window.setMouseCursorVisible(1);
			leaderBoard->draw(window);
		}
		else if (state == PAUSED_S) {
			window.setMouseCursorVisible(1);
			gamePause->draw(window);
		}
		else if (state == GAMEOVER_S) {
			window.setMouseCursorVisible(1);
			enterName->draw(window);
		}

		window.display();
	}

	return 0;
}