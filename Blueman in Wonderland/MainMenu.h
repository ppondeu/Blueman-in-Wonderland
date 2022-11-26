#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
class MainMenu
{
private:
	sf::Font font;
	
	const unsigned short characterSize = 90;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	int cntOnPlay = 0, cntOnTutorials = 0, cntOnLeaderboard = 0, cntOnExit = 0;
	
public:
	sf::Text title, play, tutorials, leaderboard, exit, gameDev;
	bool isThemeSoundPlay = true;
private:
	void isOnButton(const sf::Vector2f& mousePos);
public:
	MainMenu();
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow &window);
};