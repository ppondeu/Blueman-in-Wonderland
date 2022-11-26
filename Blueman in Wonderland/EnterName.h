#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<iostream>
#include<cctype>
#include<fstream>
class EnterName
{
private:
	sf::Font font;
	sf::Text victoryTxt, defeatTxt;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Text scoreTxt;
	sf::RectangleShape NameBox, submitBox;
	short cntOnSubmit = 0;

	sf::Text textEnter;
	std::stringstream textEnterSS;

	sf::Sound gameoverSound, victorySound;
	sf::SoundBuffer gameoverBF, victoryBF;
	bool isSoundPlayed = false;
	
public:
	unsigned long long score = 0;
	std::string name;
	sf::Text submitTxt;
	std::string textEnterStr;

	short isVictory = 2;  // 0->defeat , 1->victory, 2->process
	short afterSubmit = 0;
private:
	
public:
	EnterName();
	void onEvent(const sf::Event& event);
	void isOnButton(const sf::Vector2f& mousePos);
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window);

	void setIsVictory(const short isVictory);
	void engame(const short isVictory, const unsigned long long score);
	std::string getName();
	unsigned long long getScore();
	void setName(const std::string name);
};