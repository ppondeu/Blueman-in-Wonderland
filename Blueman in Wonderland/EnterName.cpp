#include "EnterName.h"

EnterName::EnterName() {
	font.loadFromFile("Font/PixelFont2.ttf");
	buffer.loadFromFile("Audio/onButtonSound.wav");
	sound.setBuffer(buffer);

	victoryTxt.setFont(font);
	victoryTxt.setCharacterSize(100);
	victoryTxt.setString("YOU WIN!");
	victoryTxt.setOrigin(victoryTxt.getGlobalBounds().width / 2, victoryTxt.getGlobalBounds().height / 2);
	victoryTxt.setOutlineThickness(5);
	victoryTxt.setOutlineColor(sf::Color::Black);
	victoryTxt.setPosition(959, 539 - 350 - 30 - 30);
	victoryTxt.setStyle(sf::Text::Bold);

	defeatTxt.setFont(font);
	defeatTxt.setCharacterSize(100);
	defeatTxt.setString("GAME OVER!");
	defeatTxt.setOrigin(defeatTxt.getGlobalBounds().width / 2, defeatTxt.getGlobalBounds().height / 2);
	defeatTxt.setOutlineThickness(5);
	defeatTxt.setOutlineColor(sf::Color::Black);
	defeatTxt.setPosition(959, 539 - 350 - 30 - 30);
	defeatTxt.setStyle(sf::Text::Bold);

	scoreTxt.setFont(font);
	scoreTxt.setCharacterSize(50);
	std::stringstream ss;
	ss << "SCORE : " << score;
	scoreTxt.setString(ss.str());
	ss.str("");
	scoreTxt.setOrigin(scoreTxt.getGlobalBounds().width / 2, scoreTxt.getGlobalBounds().height / 2);
	scoreTxt.setOutlineThickness(5);
	scoreTxt.setOutlineColor(sf::Color::Black);
	scoreTxt.setPosition(959-10, 539 - 350 - 30 - 30+200);

	submitTxt.setFont(font);
	submitTxt.setCharacterSize(50);
	submitTxt.setString("SUBMIT");
	submitTxt.setOrigin(submitTxt.getGlobalBounds().width / 2, submitTxt.getGlobalBounds().height / 2);
	submitTxt.setOutlineThickness(5);
	submitTxt.setOutlineColor(sf::Color::Black);
	submitTxt.setPosition(959 - 10, 539 - 350 - 30 - 30 + 600-25);
	
	
	NameBox.setSize(sf::Vector2f(600, 100));
	NameBox.setOrigin(NameBox.getGlobalBounds().width / 2, NameBox.getGlobalBounds().height / 2);
	NameBox.setFillColor(sf::Color(170, 170, 170, 255));
	NameBox.setOutlineColor(sf::Color::Black);
	NameBox.setOutlineThickness(-5);
	NameBox.setPosition(959 - 10, 539 - 350 - 30 - 30 + 500);

	submitBox.setSize(sf::Vector2f(200, 70));
	submitBox.setOrigin(submitBox.getGlobalBounds().width / 2, submitBox.getGlobalBounds().height / 2);
	submitBox.setFillColor(sf::Color(170, 170, 170, 255));
	submitBox.setOutlineColor(sf::Color::Black);
	submitBox.setOutlineThickness(-5);
	submitBox.setPosition(959 - 10, 539 - 350 - 30 - 30 + 600+21-25);

	textEnterStr = "";

	gameoverBF.loadFromFile("Audio/gameoverSound.wav");
	gameoverSound.setBuffer(gameoverBF);

	victoryBF.loadFromFile("Audio/victorySound.wav");
	victorySound.setBuffer(victoryBF);
}

void EnterName::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::TextEntered) {
		if (((event.text.unicode >= '0' && event.text.unicode <= '9') ||( event.text.unicode >= 'a' && event.text.unicode <= 'z' ) 
			|| (event.text.unicode >= 'A' && event.text.unicode <= 'Z')) && textEnterStr.size() < 10) {
			char c = std::toupper((char)event.text.unicode);
			textEnterStr += c;
		}
	}
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::BackSpace) {
			if (textEnterStr != "") {
				textEnterStr.pop_back();
			}
		}
	}
	
	
}
void EnterName::isOnButton(const sf::Vector2f& mousePos) {
	if (submitBox.getGlobalBounds().contains(mousePos)) {
		++cntOnSubmit;
		if (cntOnSubmit == 1) sound.play();
		submitTxt.setFillColor(sf::Color::Yellow);
	}
	else {
		cntOnSubmit = 0;
		submitTxt.setFillColor(sf::Color::White);
	}
}
void EnterName::onUpdate(const sf::Vector2f& mousePos) {
	if (!isSoundPlayed) {
		if (isVictory == 0) {
			gameoverSound.play();
			isSoundPlayed = true;
		}
		else if (isVictory == 1) {
			victorySound.play();
			isSoundPlayed = true;
		}
	}
	isOnButton(mousePos);
	
}
void EnterName::draw(sf::RenderWindow& window) {
	if (isVictory==1) {
		window.draw(victoryTxt);
		std::stringstream ss;
		ss << "SCORE : " << score;
		scoreTxt.setString(ss.str());
		
	}
	else if (isVictory == 0) {
		window.draw(defeatTxt);
		std::stringstream ss;
		ss << "SCORE : " << score;
		scoreTxt.setString(ss.str());
		
	}

	
	window.draw(scoreTxt);
	window.draw(NameBox);
	window.draw(submitBox);
	window.draw(submitTxt);

	sf::Text tempTextEnter;
	tempTextEnter.setFont(font);
	
	if (textEnterStr == "") {
		tempTextEnter.setLetterSpacing(1);
		tempTextEnter.setCharacterSize(40);
		tempTextEnter.setString("ENTER YOUR NAME");
		tempTextEnter.setFillColor(sf::Color::White);
		tempTextEnter.setOutlineThickness(1);
		tempTextEnter.setStyle(sf::Text::Regular);
		tempTextEnter.setPosition(959 - 10 - 230+50, 539 - 350 - 30 - 30 + 500 - 30);
	}
	else {
		textEnterSS << textEnterStr;
		tempTextEnter.setString(textEnterSS.str());
		textEnterSS.str("");
		tempTextEnter.setFillColor(sf::Color::Yellow);
		tempTextEnter.setCharacterSize(70);
		tempTextEnter.setStyle(sf::Text::Bold);
		tempTextEnter.setOutlineColor(sf::Color::Black);
		tempTextEnter.setOutlineThickness(5);
		tempTextEnter.setLetterSpacing(2);
		tempTextEnter.setPosition(959 - 10 - 230-38, 539 - 350 - 30 - 30 + 500 - 45);
	}
	
	window.draw(tempTextEnter);

}

void EnterName::setIsVictory(const short isVictory) {
	this->isVictory = isVictory;
}

void EnterName::engame(const short isVictory, const unsigned long long score) {
	this->isVictory = isVictory;
	this->score = score;
}

void EnterName::setName(const std::string name) {
	this->name = name;
}
std::string EnterName::getName() {
	return name;
}

unsigned long long EnterName::getScore() {
	return score;
}