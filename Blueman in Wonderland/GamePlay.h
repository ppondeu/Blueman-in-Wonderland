#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"Gui.h"
#include"Item.h"
#include"Player.h"
#include"GamePlay.h"
#include"Boss.h"
#include"Player.h"
#include"EnemyI.h"
#include"EnemyII.h"
#include"EnemyIII.h"

class GamePlay
{
private:
	float cntDelay = 0.0f;

	short currentFade = 1;
	short currentSetOfFade = 1;

	std::vector<bool> isSpawn{ true, true, true };

	std::vector<short> amountEnemy { 25, 20, 15 };
	
	int a=0, b=0, c=0;
	int amountType = 3;
	float delay = 3.0f;
	int cntPlayer = 0;
	int amountEnemyDead = 0;

	sf::Time deltaTime = sf::seconds(1.0f/60.0f);

	
	
public:
	Gui* gui = new Gui;
	Item* item = new Item;
	Player* modelX = new Player;
	Boss* golaMoska = new Boss;
	EnemyI* skeleton = new EnemyI;
	EnemyII* eyeSaber = new EnemyII;
	EnemyIII* buffaRed = new EnemyIII;

	short isVictory = 2;  // 0 -> defeat , 1 -> victory, 2 -> process

	const float afterGameDelay = 3.0f;
	float cntAfterGame = 0.0f;
	bool isSwitchState = false;
	short gameOverCheck = 0;
	
private:
public:
	GamePlay();
	~GamePlay();
	void beforeOnEvent();
	void onEvent(const sf::Event& event);
	void onUpdate();
	void afterOnEvent();
	bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB, int topA, int leftA, int topB, int leftB, sf::Vector2i sizeA, sf::Vector2i sizeB);
	void draw(sf::RenderWindow& window);

	bool isStopPlaySound();
};