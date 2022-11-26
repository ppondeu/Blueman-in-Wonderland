#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
class LeaderBoard
{
private:
	sf::RectangleShape frame, leaderBoardFrame;
	const short maxPlayer = 5;
	std::vector<sf::RectangleShape> playerScoreFrame;
	std::vector<sf::Text> playerScoreTxt;
	std::vector<sf::Text> playerNameTxt;
	sf::Font font;
	
	sf::RectangleShape menuFrame, playAgainFrame;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	short cntOnMenu = 0;
	short cntOnPlayAgain = 0;

	// if last state = game play state make function to request texture from the last scence of game state to display at gameoverstate;

	unsigned long long score = 0;
	std::string name = "";
	std::vector<std::pair<std::pair<std::string, std::string>, unsigned long long>> data;

	bool once = false;

	
public:
	short lastState = 0;
	sf::Text leaderBoardTxt, menuTxt, playAgainTxt;
private:
	void readFile();
	void updateLeaderBoard();
	void setLeaderBoard();
	void writeFile();
public:
	LeaderBoard();
	void isOnButton(const sf::Vector2f& mousePos);
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window);
	void setLastState(const short lastState);

	void setData(const std::string name, const unsigned long long score);
};