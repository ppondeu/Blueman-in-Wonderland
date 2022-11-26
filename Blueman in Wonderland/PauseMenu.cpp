#include "PauseMenu.h"

PauseMenu::PauseMenu() {
	font.loadFromFile("Font/PixelFont2.ttf");
	buffer.loadFromFile("Audio/onButtonSound.wav");
	sound.setBuffer(buffer);

	pauseTxt.setFont(font);
	pauseTxt.setCharacterSize(55);
	pauseTxt.setString("GAME PAUSED");
	pauseTxt.setOrigin(pauseTxt.getGlobalBounds().width / 2, pauseTxt.getGlobalBounds().height / 2);
	pauseTxt.setPosition(959 - 10, 539 - 350 - 30 - 30+200+10);

	pauseFrame.setSize(sf::Vector2f(600, 100));
	pauseFrame.setFillColor(sf::Color(13, 58, 58, 255));
	pauseFrame.setOutlineColor(sf::Color(176, 190, 187, 255));
	pauseFrame.setOutlineThickness(-10);
	pauseFrame.setOrigin(pauseFrame.getGlobalBounds().width / 2, pauseFrame.getGlobalBounds().height / 2);
	pauseFrame.setPosition(959, 539 - 350 - 30+200);

	sf::RectangleShape tempMenu;
	tempMenu.setSize(sf::Vector2f(550, 100));
	tempMenu.setFillColor(sf::Color(13, 58, 58, 255));
	tempMenu.setOutlineColor(sf::Color(176, 190, 187, 255));
	tempMenu.setOutlineThickness(-10);
	tempMenu.setOrigin(tempMenu.getGlobalBounds().width / 2, tempMenu.getGlobalBounds().height);
	for (int i = 0; i < 3; i++) {
		pauseMenuFrame.push_back(tempMenu);
		pauseMenuFrame.back().setPosition(959, 539 - 160 + 130*i+200);
	}

	resumeTxt.setFont(font);
	resumeTxt.setCharacterSize(50);
	resumeTxt.setString("RESUME");
	resumeTxt.setOrigin(resumeTxt.getGlobalBounds().width / 2, resumeTxt.getGlobalBounds().height / 2);
	resumeTxt.setPosition(959, 539 - 160 + 125+5 );

	restartTxt.setFont(font);
	restartTxt.setCharacterSize(50);
	restartTxt.setString("RESTART");
	restartTxt.setOrigin(restartTxt.getGlobalBounds().width / 2, restartTxt.getGlobalBounds().height / 2);
	restartTxt.setPosition(959, 539 - 160 + 125 + 130+5);

	homeTxt.setFont(font);
	homeTxt.setCharacterSize(50);
	homeTxt.setString("HOME");
	homeTxt.setOrigin(homeTxt.getGlobalBounds().width / 2, homeTxt.getGlobalBounds().height / 2);
	homeTxt.setPosition(959, 539 - 160 + 125 + 130*2+5);
}

void PauseMenu::isOnButton(const sf::Vector2f& mousePos) {
	for (int i = 0; i < 3; i++) {
		if (pauseMenuFrame[i].getGlobalBounds().contains(mousePos)) {
			if (i == 0) {
				++cntOnResume;
				if (cntOnResume == 1) {
					sound.play();
				}
				resumeTxt.setFillColor(sf::Color::Red);
			}
			else if (i == 1) {
				++cntOnRestart;
				if (cntOnRestart == 1) {
					sound.play();
				}
				restartTxt.setFillColor(sf::Color::Red);
			}
			else if (i == 2) {
				++cntOnHome;
				if (cntOnHome == 1) {
					sound.play();
				}
				homeTxt.setFillColor(sf::Color::Red);
			}
			break;
		}
		else {
			if (i == 0) {
				cntOnResume = 0;
				resumeTxt.setFillColor(sf::Color::White);
			}
			else if (i == 1) {
				cntOnRestart = 0;
				restartTxt.setFillColor(sf::Color::White);
			}
			else if (i == 2) {
				cntOnHome = 0;
				homeTxt.setFillColor(sf::Color::White);
			}
		}
	}
}

void PauseMenu::onUpdate(const sf::Vector2f& mousePos) {
	isOnButton(mousePos);
}

void PauseMenu::draw(sf::RenderWindow& window) {
	window.draw(pauseFrame);
	window.draw(pauseTxt);
	for (int i = 0; i < 3; i++) {
		window.draw(pauseMenuFrame[i]);
	}
	window.draw(resumeTxt);
	window.draw(restartTxt);
	window.draw(homeTxt);
}
