#include "MainMenu.h"

MainMenu::MainMenu() {
	font.loadFromFile("Font/PixelFont2.ttf");

	title.setFont(font);
	title.setCharacterSize(characterSize + 10);
	title.setString("BLUEMAN IN WONDERLAND");
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
	title.setPosition(959, 150 - title.getGlobalBounds().height / 2);
	title.setFillColor(sf::Color::Yellow);
	title.setOutlineColor(sf::Color::Red);
	title.setOutlineThickness(-2);
	//title.setStyle(sf::Text::Italic);
	title.setStyle(sf::Text::Bold);


	play.setFont(font);
	play.setCharacterSize(characterSize);
	play.setString("PLAY");
	play.setOrigin(play.getGlobalBounds().width / 2, play.getGlobalBounds().height / 2);
	play.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200);
	play.setFillColor(sf::Color::White);
	//play.setStyle(sf::Text::Italic);

	tutorials.setFont(font);
	tutorials.setCharacterSize(characterSize);
	tutorials.setString("TUTORIALS");
	tutorials.setOrigin(tutorials.getGlobalBounds().width / 2, tutorials.getGlobalBounds().height / 2);
	tutorials.setPosition(960, 150 - title.getGlobalBounds().height / 2 + 200 + 125);
	tutorials.setFillColor(sf::Color::White);
	//tutorials.setStyle(sf::Text::Italic);

	leaderboard.setFont(font);
	leaderboard.setCharacterSize(characterSize);
	leaderboard.setString("LEADERBOARD");
	leaderboard.setOrigin(leaderboard.getGlobalBounds().width / 2, leaderboard.getGlobalBounds().height / 2);
	leaderboard.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 2);
	leaderboard.setFillColor(sf::Color::White);
	//leaderboard.setStyle(sf::Text::Italic);

	exit.setFont(font);
	exit.setCharacterSize(characterSize);
	exit.setString("EXIT");
	exit.setOrigin(exit.getGlobalBounds().width / 2, exit.getGlobalBounds().height / 2);
	exit.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 3);
	exit.setFillColor(sf::Color::White);
	//exit.setStyle(sf::Text::Italic);

	gameDev.setFont(font);
	gameDev.setCharacterSize(20);
	gameDev.setString("Developed by 65010539 Nitcharat Thatthiam");
	gameDev.setOrigin(gameDev.getGlobalBounds().width / 2, gameDev.getGlobalBounds().height / 2);
	gameDev.setPosition(1919 - gameDev.getGlobalBounds().width / 2 - 30, 1079 - gameDev.getGlobalBounds().height - 30);
	gameDev.setFillColor(sf::Color(255, 255, 255, 100));
	gameDev.setStyle(sf::Text::Underlined);

	buffer.loadFromFile("Audio/onButtonSound.wav");
	sound.setBuffer(buffer);
}

void MainMenu::isOnButton(const sf::Vector2f& mousePos) {
	sf::Text tempPlay = play;
	tempPlay.setCharacterSize(characterSize);
	tempPlay.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200);

	sf::Text tempTutorials = tutorials;
	tempTutorials.setCharacterSize(characterSize);
	tempTutorials.setPosition(960, 150 - title.getGlobalBounds().height / 2 + 200 + 125);

	sf::Text tempLeaderboard = leaderboard;
	tempLeaderboard.setCharacterSize(characterSize);
	tempLeaderboard.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 2);

	sf::Text tempExit = exit;
	tempExit.setCharacterSize(characterSize);
	tempExit.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 3);

	if (tempPlay.getGlobalBounds().contains(mousePos)) {
		++cntOnPlay;
		if (cntOnPlay == 1) {
			sound.play();
		}

		play.setFillColor(sf::Color::Yellow);
		play.setPosition(959 - 30, 150 - title.getGlobalBounds().height / 2 + 200);
		play.setCharacterSize(characterSize + 10);
	}
	else {
		cntOnPlay = 0;
		play.setFillColor(sf::Color::White);
		play.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200);
		play.setCharacterSize(characterSize);
	}

	if (tempTutorials.getGlobalBounds().contains(mousePos)) {
		++cntOnTutorials;
		if (cntOnTutorials == 1) {
			sound.play();
		}
		tutorials.setFillColor(sf::Color::Yellow);
		tutorials.setPosition(959 - 30, 150 - title.getGlobalBounds().height / 2 + 200 + 125);
		tutorials.setCharacterSize(characterSize + 10);

	}
	else {
		cntOnTutorials = 0;
		tutorials.setFillColor(sf::Color::White);
		tutorials.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125);
		tutorials.setCharacterSize(characterSize);
	}
	if (tempLeaderboard.getGlobalBounds().contains(mousePos)) {
		++cntOnLeaderboard;
		if (cntOnLeaderboard == 1) {
			sound.play();
		}
		leaderboard.setFillColor(sf::Color::Yellow);
		leaderboard.setPosition(959 - 30, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 2);
		leaderboard.setCharacterSize(characterSize + 10);

	}
	else {
		cntOnLeaderboard = 0;
		leaderboard.setFillColor(sf::Color::White);
		leaderboard.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 2);
		leaderboard.setCharacterSize(characterSize);
	}
	if (tempExit.getGlobalBounds().contains(mousePos)) {
		++cntOnExit;
		if (cntOnExit == 1) {
			sound.play();
		}
		exit.setFillColor(sf::Color::Yellow);
		exit.setPosition(959 - 30, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 3);
		exit.setCharacterSize(characterSize + 10);
	}
	else {
		cntOnExit = 0;
		exit.setFillColor(sf::Color::White);
		exit.setPosition(959, 150 - title.getGlobalBounds().height / 2 + 200 + 125 * 3);
		exit.setCharacterSize(characterSize);
	}
}

void MainMenu::onUpdate(const sf::Vector2f& mousePos) {
	isOnButton(mousePos);

}
void MainMenu::draw(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.loadFromFile("Sprite/Background/mainMenu.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 1079 - sprite.getGlobalBounds().height);
	window.draw(sprite);
	window.draw(title);
	window.draw(play);
	window.draw(tutorials);
	window.draw(leaderboard);
	window.draw(exit);
	window.draw(gameDev);

}