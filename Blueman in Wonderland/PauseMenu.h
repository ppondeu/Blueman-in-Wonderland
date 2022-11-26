#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
class PauseMenu
{
private:
	sf::Font font;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	short cntOnResume = 0, cntOnRestart = 0, cntOnHome = 0;
	std::vector<sf::RectangleShape> pauseMenuFrame;
	sf::RectangleShape pauseFrame;
	sf::Text pauseTxt;
	
public:
	sf::Text resumeTxt, restartTxt, homeTxt;
private:
public:
	PauseMenu();
	void isOnButton(const sf::Vector2f& mousePos);
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window);
};